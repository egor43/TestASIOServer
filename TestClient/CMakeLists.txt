cmake_minimum_required(VERSION 2.8)

project(TestClient)

set(LIB boost_system boost_filesystem)

add_executable(${PROJECT_NAME} "main.cpp" "myclient.h" "my_client.cpp")

set(CMAKE_CXX_FLAGS "-std=c++14")

target_link_libraries(${PROJECT_NAME} ${LIB})
