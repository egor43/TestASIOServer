cmake_minimum_required(VERSION 2.8)

project(TestServerASIO)

set(LIB boost_system)

add_executable(${PROJECT_NAME} "main.cpp")

set(CMAKE_CXX_FLAGS "-std=c++14")

target_link_libraries(${PROJECT_NAME} ${LIB})
