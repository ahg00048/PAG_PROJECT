cmake_minimum_required(VERSION 3.29)
project(PAG_PROJECT)

set(CMAKE_CXX_STANDARD 20)

file(GLOB IMGUI_SRC_FILES imgui/src/*.cpp)
file(GLOB GLAD_SRC_FILES GLAD/src/*.c)

add_executable(PAG_PROJECT main.cpp
        Renderer/Renderer.cpp
        Renderer/Renderer.h
        GUI/GUI.cpp GUI/GUI.h
        ${IMGUI_SRC_FILES}
        ${GLAD_SRC_FILES}
        Shader/Shader.cpp
        Shader/Shader.h
        Camara/Camera.cpp
        Camara/Camera.h
        ShaderProgram/ShaderProgram.cpp
        ShaderProgram/ShaderProgram.h
        Model/Model.cpp
        Model/Model.h
        vendor/imfilebrowser.h
        Material/Material.cpp
        Material/Material.h
        Light/Light.cpp
        Light/Light.h
        Light/LightProperties.h
        Light/LightApplicator/LightApplicator.h
        Light/LightApplicator/PointLightApplicator/PointLightApplicator.cpp
        Light/LightApplicator/PointLightApplicator/PointLightApplicator.h
        Light/LightApplicator/SpotLightApplicator/SpotLightApplicator.cpp
        Light/LightApplicator/SpotLightApplicator/SpotLightApplicator.h
        Light/LightApplicator/DirectionaLightApplicator/DirectionalLightApplicator.cpp
        Light/LightApplicator/DirectionaLightApplicator/DirectionalLightApplicator.h
        Light/LightApplicator/AmbientLightApplicator/AmbientLightApplicator.cpp
        Light/LightApplicator/AmbientLightApplicator/AmbientLightApplicator.h
        Texture/Texture.cpp
        Texture/Texture.h)

target_include_directories(${PROJECT_NAME} PUBLIC imgui/headers)
target_include_directories(${PROJECT_NAME} PUBLIC GLAD/include)

find_package(assimp)
find_package(opengl_system)
find_package(glm)
find_package(lodepng)
find_package(glfw3)

# Then, link your executable or library with the corresponding package targets:

target_link_libraries(PAG_PROJECT
        assimp::assimp
        opengl::opengl
        glm::glm
        lodepng::lodepng
        glfw)