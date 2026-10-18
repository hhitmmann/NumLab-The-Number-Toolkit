cmake_minimum_required(VERSION 3.20)
project(CalcLab VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(calclab
    src/base_converter.cpp
    src/calculator.cpp
    src/data_type_converter.cpp
    src/operator_lab.cpp
    src/overflow_precision.cpp
    src/scientific_function.cpp
    src/ui_choices.cpp
)
target_include_directories(calclab PUBLIC include)

add_executable(calclab_app apps/main.cpp)
target_link_libraries(calclab_app PRIVATE calclab)

foreach(target calclab calclab_app)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endforeach()