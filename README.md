# Viscii
A simple application to view videos as colored ASCII characters in the terminal.

Currently only works on Windows!

## Requirements:
- CMake 3.16
- C++ 20

## Build
1. Create build directory
```bash
mkdir build
cd build
```
2. Build project
```bash
cmake ..
cmake --build .
```

3. Run project
```bash
.\bin\viscii.exe <path/to/file>
.\bin\viscii.exe # uses default video
```
