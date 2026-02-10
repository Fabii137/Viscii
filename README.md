# Viscii
A simple application to view videos as colored ASCII characters in the terminal.

## Requirements:
- CMake 3.16
- C++ 20

### Linux Dependencies
Install pkg-config and a video backend:
```bash
sudo apt install pkg-config

# FFmpeg (recommended)
sudo apt install libavcodec-dev libavformat-dev libavutil-dev libswscale-dev

# OR GStreamer
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
```

### macOS Dependencies
Install pkg-config and ffmpeg:
```bash
brew install pkg-config ffmpeg
```

### Windows
No additional dependencies required - uses built-in Media Foundation.

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
# Windows
.\bin\viscii.exe <path/to/file>
.\bin\viscii.exe # uses default video

# Linux / macOS
./bin/viscii <path/to/file>
./bin/viscii # uses default video
```
