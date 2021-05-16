cmake_minimum_required(VERSION 3.10)

# Project name
project(TriColor)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Packages
find_package(OpenCV REQUIRED)
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

# Executable details
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Executable
add_executable(TriColor main.cpp)


# Link libraries
target_link_libraries(
    TriColor
    ${OpenCV_LIBS}
)

