cmake_minimum_required(VERSION 3.13)
project(RayTracer LANGUAGES CXX)

add_compile_options(-O3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Catch undefined behaviour
#set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")

# Gather source files
file(GLOB LIB_SOURCES src/*.cpp)

# Create the library
add_library(RayTracerLib ${LIB_SOURCES})

# Include directories
target_include_directories(RayTracerLib
  PUBLIC include
  PRIVATE src
)

# Build example executable
add_executable(main)
target_sources(main
  PRIVATE
  examples/main.cpp
)
target_link_libraries(main PRIVATE RayTracerLib)

