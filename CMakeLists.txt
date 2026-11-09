cmake_minimum_required(VERSION 3.20)
project(NumLab VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Without a build type CMake compiles with no optimisation at all, so default to Release.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Release: optimise for small size.
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O1 /DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")
endif()


include(CheckIPOSupported)
check_ipo_supported(RESULT NUMLAB_IPO_OK OUTPUT NUMLAB_IPO_MSG LANGUAGES CXX)
if(NUMLAB_IPO_OK)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()


# Everything except main() lives in a library, so the tests can link against it too.
add_library(numlab_core
    src/base_converter/Base_Converter.cpp
    src/Calculator/Calculator.cpp
    src/Calculator/MathOps.cpp
    src/data_type/Data_Type_Converter.cpp
    src/operator_lab/Operator_Lab.cpp
    src/Overflow_Precision/Overflow_Precision.cpp
    src/Scientific_Function/Scientific_Function.cpp
    src/UI/ClearScreen.cpp
    src/UI/UI_Choices.cpp
)
target_include_directories(numlab_core PUBLIC include)

add_executable(numlab apps/main.cpp)
target_link_libraries(numlab PRIVATE numlab_core)

foreach(target numlab_core numlab)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
                target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -ffunction-sections -fdata-sections)
    endif()
endforeach()


# Release executable: drop unused sections and (on Linux / MinGW) strip the symbol table.
if(APPLE)
    target_link_options(numlab PRIVATE "$<$<CONFIG:Release>:-Wl,-dead_strip>")
elseif(NOT MSVC)
    target_link_options(numlab PRIVATE "$<$<CONFIG:Release>:-Wl,--gc-sections>" "$<$<CONFIG:Release>:-s>")
endif()


# Unit tests: picked up automatically once a tests/CMakeLists.txt file exists.
enable_testing()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()