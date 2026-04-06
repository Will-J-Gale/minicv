cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)

project("minicv")

add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE SRC_FILES    
    "src/*.cpp"
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    include/
)

target_precompile_headers(
    ${PROJECT_NAME}
    PUBLIC
    include/pch.h
)

add_subdirectory(examples)