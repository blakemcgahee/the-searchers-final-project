# This is your main CMakeLists.txt file.
# It tells CMake how to build your project.

# Minimum version of CMake required.
cmake_minimum_required(VERSION 3.22)

# Name your project. This should match your project title.
project(EfficientDataRetrieval)

# Set the C++ standard to C++14.
set(CMAKE_CXX_STANDARD 14)

# Add your source directories to the include path.
# This allows you to use #include "MyHeader.h" instead of #include "src/MyHeader.h".
include_directories(src test)

# Define your main executable.
# You will add your .cpp and .h files here.
add_executable(Main
    src/main.cpp
    # Add other .cpp and .h files here, e.g., src/ProjectUtils.h
)

# Define your test executable (if you have one).
# This will link against Catch2 for testing.
add_executable(Tests
    test/test.cpp
    # Add other .cpp and .h files here that your tests depend on.
)

# You'll need to add Catch2 integration here later if your template didn't provide it.
# For now, this minimal shell just sets up the basic executables.
# For example, to link Catch2:
# target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

# You might also add CTest integration for test discovery.
# include(CTest)
# include(Catch)
# catch_discover_tests(Tests)
