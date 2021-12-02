cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-D STB_IMAGE_WRITE_IMPLEMENTATION)

#find_package(OpenCV)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${RayTracing_SOURCE_DIR}/include)
include_directories(${RayTracing_SOURCE_DIR}/thirdparty)

add_executable(RayTracing src/main.cpp src/Ray.cpp src/Hittable.cpp src/Camera.cpp src/Sphere.cpp include/Material.h src/Lambertain.cpp src/MetalMaterial.cpp src/DielectricMaterial.cpp)
#target_link_libraries(RayTracing ${OpenCV_LIBS} pthread)