#include <torch/script.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

static const std::string DEFAULT_MODEL_PATH = "/home/models/model.pt";
static const int INPUT_DIMENSION = 135;

std::vector<float> readInputModules()
{
    // In real embedded deployment this section should read
    // sensor / DAQ modules (ADC, SPI devices, shared memory, etc).
    // For now it is replaced with dummy data generation.

    std::vector<float> data(INPUT_DIMENSION);

    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (auto &v : data)
        v = dist(gen);

    return data;
}

std::vector<float> runInference(torch::jit::script::Module &model, const std::vector<float> &input)
{
    torch::Tensor input_tensor = torch::from_blob(
        const_cast<float *>(input.data()),
        {1, (long)INPUT_DIMENSION},
        torch::kFloat32).clone();

    torch::NoGradGuard no_grad;

    torch::Tensor output = model.forward({input_tensor}).toTensor();

    std::vector<float> result;
    auto acc = output.accessor<float,2>();

    for (int i = 0; i < output.size(1); ++i)
        result.push_back(acc[0][i]);

    return result;
}

void writeOutputModules(const std::vector<float> &output)
{
    // In production this section should write the results to
    // hardware modules, shared memory, fieldbus, or control outputs.
    // For now it is replaced with logs.

    std::cout << "Inference Output: ";

    for (size_t i = 0; i < output.size(); ++i)
    {
        std::cout << output[i];
        if (i != output.size() - 1)
            std::cout << ", ";
    }

    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    std::string model_path = DEFAULT_MODEL_PATH;

    if (argc > 1)
        model_path = argv[1];

    torch::jit::script::Module model;

    try
    {
        model = torch::jit::load(model_path, torch::kCPU);
        model.eval();
    }
    catch (const c10::Error &e)
    {
        std::cerr << "Model load failed: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Model loaded from: " << model_path << std::endl;

    while (true)
    {
        // STEP 1 — READ INPUT MODULES
        std::vector<float> input_data = readInputModules();

        // STEP 2 — RUN MODEL INFERENCE
        std::vector<float> output = runInference(model, input_data);

        // STEP 3 — WRITE OUTPUT MODULES
        writeOutputModules(output);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
