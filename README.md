# DAQ Data Streaming

For detailed documentation, refer to:  
[NI Linux RT Cross-Compile Guide](https://nilrt-docs.ni.com/cross_compile/config_vs_code.html)


**Note:** This will only work on Windows OS.

---

## Steps for compiling

#### 1. Create ```CMakeLists.txt```
Add the necessary libraries and C++ configurations in the `CMakeLists.txt` file.


#### 2. Build the Project
In the terminal, navigate to the root path of the project and run the following commands:

```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```
