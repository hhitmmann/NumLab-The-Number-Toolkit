cmake_minimum_required(VERSION 3.20)
project(NumLab VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Everything except main() lives in a library, so the tests can link against it too.
add_library(numlab_core
    src/Base_Converter.cpp
    src/Calculator.cpp
    src/ClearScreen.cpp
    src/Data_Type_Converter.cpp
    src/MathOps.cpp
    src/Operator_Lab.cpp
    src/Overflow_Precision.cpp
    src/Scientific_Function.cpp
    src/UI_Choices.cpp
)
target_include_directories(numlab_core PUBLIC include)

add_executable(numlab apps/main.cpp)
target_link_libraries(numlab PRIVATE numlab_core)

foreach(target numlab_core numlab)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()

# Unit tests: picked up automatically once a tests/CMakeLists.txt file exists.
enable_testing()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()
