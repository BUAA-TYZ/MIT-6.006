cmake_minimum_required(VERSION 3.5)
PROJECT(AVL_TREE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

message(${PROJECT_SOURCE_DIR})

add_executable(main.exe src/main.cpp)

target_include_directories(main.exe
    PRIVATE ${PROJECT_SOURCE_DIR}/include)
