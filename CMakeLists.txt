cmake_minimum_required(VERSION 3.29)
project(PAG_PROJECT)

set(CMAKE_CXX_STANDARD 20)

add_executable(PAG_PROJECT main.cpp)

find_package(assimp)
find_package(opengl_system)
find_package(glm)
find_package(lodepng)
find_package(glfw3)
find_package(glad)
find_package(imgui)

# Then, link your executable or library with the corresponding package targets:

target_link_libraries(PAG_PROJECT
        assimp::assimp
        opengl::opengl
        glm::glm
        lodepng::lodepng
        glfw
        glad::glad
        imgui::imgui)