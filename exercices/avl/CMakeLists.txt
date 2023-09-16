cmake_minimum_required(VERSION 3.5)
PROJECT(AVL_TREE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/test/googletest-1.14.0)
add_executable(main src/main.cpp src/unit_test.cpp)

target_include_directories(main
    PRIVATE ${PROJECT_SOURCE_DIR}/includes)

target_link_libraries(main
  GTest::gtest_main
)