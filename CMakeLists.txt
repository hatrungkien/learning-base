cmake_minimum_required(VERSION 3.24)
project(debug)

set(CMAKE_CXX_STANDARD 14)
add_executable(debug main.cpp)

target_link_libraries(debug paho-mqttpp3 paho-mqtt3c)

