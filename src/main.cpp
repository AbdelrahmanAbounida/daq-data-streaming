#include <stdio.h>
#include <stdlib.h>
#include <NIDAQmx.h>


void handleError(int32 error) {
    if (error) {
        char errorBuffer[2048];
        DAQmxGetErrorString(error, errorBuffer, 2048);
        printf("DAQmx Error: %s\n", errorBuffer);
        exit(1);
    }
}

int main(void) {
    puts("First NIDAQmx Task ");
    // TaskHandle taskHandle = 0;
    // int32 error = 0;

    // error = DAQmxCreateTask("", &taskHandle);
    // handleError(error);

    // error = DAQmxCreateAOVoltageChan(taskHandle, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, NULL);
    // handleError(error);

    // // Create an analog input channel (reading from device)
    // error = DAQmxCreateAIVoltageChan(taskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL);
    // handleError(error);

    // // Start the task
    // error = DAQmxStartTask(taskHandle);
    // handleError(error);

    // // Write a voltage value to the output channel (e.g., 5V)
    // float64 writeValue = 5.0;
    // error = DAQmxWriteAnalogF64(taskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &writeValue, NULL, NULL);
    // handleError(error);

    // // Read the voltage value from the input channel
    // float64 readValue = 0.0;
    // error = DAQmxReadAnalogF64(taskHandle, 1, 10.0, DAQmx_Val_GroupByChannel, &readValue, 1, NULL, NULL);
    // handleError(error);

    // printf("Read Value: %f V\n", readValue);

    // // Stop and clear the task
    // error = DAQmxStopTask(taskHandle);
    // handleError(error);
    // error = DAQmxClearTask(taskHandle);
    // handleError(error);

    return EXIT_SUCCESS;
}
