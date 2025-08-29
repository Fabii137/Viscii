cmake_minimum_required(VERSION 3.16)
project(Viscii)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) # LTO

# ---- MSVC runtime settings ----
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2) # enable SIMD
endif()

# Point CMake to the extracted OpenCV package
set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/opencv/build/x64/vc16/lib")

find_package(OpenCV 4 REQUIRED)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${MY_SOURCES})


if(PRODUCTION_BUILD)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC
        RESOURCES_PATH="./resources/"
        PRODUCTION_BUILD=1
    )
else()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC
        RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
        PRODUCTION_BUILD=0
    )
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OpenCV_LIBS}
)