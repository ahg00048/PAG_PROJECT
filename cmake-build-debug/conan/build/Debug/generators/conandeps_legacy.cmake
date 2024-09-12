message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(glm)
find_package(lodepng)
find_package(assimp)
find_package(imgui)
find_package(glfw3)
find_package(opengl_system)
find_package(glad)

set(CONANDEPS_LEGACY  glm::glm  lodepng::lodepng  assimp::assimp  imgui::imgui  glfw  opengl::opengl  glad::glad )