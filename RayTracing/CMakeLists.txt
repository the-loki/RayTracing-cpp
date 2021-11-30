cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

#find_package(OpenCV)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${RayTracing_SOURCE_DIR}/include)

add_executable(RayTracing main.cpp src/Ray.cpp src/Hittable.cpp src/Camera.cpp src/Sphere.cpp)
#target_link_libraries(RayTracing ${OpenCV_LIBS} pthread)