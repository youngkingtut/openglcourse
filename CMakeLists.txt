cmake_minimum_required(VERSION 3.14)
project(udemy)

set(CMAKE_CXX_STANDARD 11)

# Project folder structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_SOURCE_DIR src)
set(EXTERNAL_LIBRARIES ext)

# Build ext
add_subdirectory("${EXTERNAL_LIBRARIES}/glew/build/cmake")
add_subdirectory("${EXTERNAL_LIBRARIES}/glfw")
add_subdirectory("${EXTERNAL_LIBRARIES}/glm")

# Include ext
include_directories("${EXTERNAL_LIBRARIES}/glew/include")
include_directories("${EXTERNAL_LIBRARIES}/glfw/include")
include_directories("${EXTERNAL_LIBRARIES}/glm")

# Create executable and link libraries
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glew ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
