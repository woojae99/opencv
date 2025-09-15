cmake_minimum_required(VERSION 3.2)
project(opencv_practice VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV include dir: ${OpenCV_INCLUDE_DIRS}")

add_executable(opencv_practice main.cpp)
target_link_libraries(opencv_practice PRIVATE ${OpenCV_LIBS})
target_include_directories(opencv_practice PRIVATE ${OpenCV_INCLUDE_DIRS})