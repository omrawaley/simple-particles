cmake_minimum_required(VERSION 3.4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(SimpleParticles)

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})

set(LIB_DIR lib)
link_directories(${LIB_DIR})

set(SRC_DIR src)
add_executable(program ${SRC_DIR}/main.cpp ${SRC_DIR}/vector2.cpp ${SRC_DIR}/particles/particleSystem.cpp)

target_link_libraries(program SDL2 SDL2_image)