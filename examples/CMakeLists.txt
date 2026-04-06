cmake_minimum_required(VERSION 3.25)
project(minicv_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    ${OpenCV_INCLUDE_DIRS}
    include
)

target_link_libraries(
    ${PROJECT_NAME} 
    ${OpenCV_LIBRARIES}
    minicv
)