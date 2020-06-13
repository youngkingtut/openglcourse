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
include_directories("${EXTERNAL_LIBRARIES}/stb")

# Create executable and link libraries
add_executable(
        ${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/Mesh.cpp
        ${PROJECT_SOURCE_DIR}/Mesh.h
        ${PROJECT_SOURCE_DIR}/Shader.cpp
        ${PROJECT_SOURCE_DIR}/Shader.h
        ${PROJECT_SOURCE_DIR}/Window.cpp
        ${PROJECT_SOURCE_DIR}/Window.h
        ${PROJECT_SOURCE_DIR}/Camera.cpp
        ${PROJECT_SOURCE_DIR}/Camera.h
        ${PROJECT_SOURCE_DIR}/Texture.cpp
        ${PROJECT_SOURCE_DIR}/Texture.h
        ${PROJECT_SOURCE_DIR}/Light.cpp
        ${PROJECT_SOURCE_DIR}/Light.h
        src/Material.cpp src/Material.h src/DirectionalLight.cpp src/DirectionalLight.h src/PointLight.cpp src/PointLight.h src/CommonValues.h src/SpotLight.cpp src/SpotLight.h)

target_link_libraries(${PROJECT_NAME} glew ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})


# Copy Resource Folder
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/src/Resources
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources
)
