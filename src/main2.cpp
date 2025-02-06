#include <iostream>
#include <NIDAQmx.h> 

int main() {
    TaskHandle taskHandle = 0;
    float64 data;
    int32 error;
    
    // Create the task
    error = DAQmxCreateTask("", &taskHandle);
    if (error != 0) {
        std::cerr << "Failed to create task! Error code: " << error << std::endl;
        return -1;
    }
    
    // Create an analog input voltage channel
    error = DAQmxCreateAIVoltageChan(taskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, nullptr);
    if (error != 0) {
        std::cerr << "Failed to create AI voltage channel! Error code: " << error << std::endl;
        DAQmxClearTask(taskHandle);  // Clean up
        return -1;
    }
    
    // Start the task
    error = DAQmxStartTask(taskHandle);
    if (error != 0) {
        std::cerr << "Failed to start the task! Error code: " << error << std::endl;
        DAQmxClearTask(taskHandle);  // Clean up
        return -1;
    }
    
    // Read the voltage from the channel
    error = DAQmxReadAnalogScalarF64(taskHandle, 10.0, &data, nullptr);
    if (error != 0) {
        std::cerr << "Failed to read the voltage! Error code: " << error << std::endl;
        DAQmxClearTask(taskHandle);  // Clean up
        return -1;
    }
    
    // Print the measured voltage
    std::cout << "Measured Voltage: " << data << " V" << std::endl;

    // Clean up
    DAQmxClearTask(taskHandle);
    
    return 0;
}
