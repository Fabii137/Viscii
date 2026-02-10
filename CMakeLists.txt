cmake_minimum_required(VERSION 3.16)
project(viscii)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# OpenCV configuration
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/OpenCVConfig.cmake)

# Fetch and build OpenCV
FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG        4.12.0
    GIT_SHALLOW    TRUE 
)
FetchContent_MakeAvailable(opencv)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/include"
    ${OPENCV_CONFIG_FILE_INCLUDE_DIR}
    ${OPENCV_MODULE_opencv_core_LOCATION}/include
    ${OPENCV_MODULE_opencv_imgproc_LOCATION}/include
    ${OPENCV_MODULE_opencv_imgcodecs_LOCATION}/include
    ${OPENCV_MODULE_opencv_videoio_LOCATION}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_videoio
)

# Add OpenCV include directories (linking alone doesn't always propagate them)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    "${opencv_BINARY_DIR}"
)

# Setting RESOURCES_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # Set the resources path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="./resources/") # Set the resources path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
