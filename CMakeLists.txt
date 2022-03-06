cmake_minimum_required(VERSION 3.21)
project(Raytracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Raytracer src/main.cpp src/Ray.cpp src/Ray.h src/objects/RaytracedObject.cpp src/objects/RaytracedObject.h src/World.cpp src/World.h src/Material.cpp src/Material.h src/simplerandom.h src/simplerandom.cpp src/objects/Plane.cpp src/objects/Plane.h src/Denoiser.cpp src/Denoiser.h src/Image.cpp src/Image.h ThreadUtilities.cpp ThreadUtilities.h)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Raytracer PRIVATE glm::glm)

find_package(libpng CONFIG REQUIRED)
target_link_libraries(Raytracer PRIVATE png_static)

find_path(PNGPP_INCLUDE_DIRS "png++/color.hpp")
target_include_directories(Raytracer PRIVATE ${PNGPP_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Raytracer PRIVATE Threads::Threads)

if(DEFINED PROFILE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    endif()