cmake_minimum_required(VERSION 3.10)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(Sandbox main.cpp Cell.cpp base.cpp placing.cpp rendering.cpp simulating.cpp)
target_link_libraries(Sandbox sfml-graphics sfml-window sfml-system)
