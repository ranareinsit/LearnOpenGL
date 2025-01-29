# CMakeList.txt : CMake project for opengl-suffering, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.29)
cmake_policy(SET CMP0141 NEW)
#
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# https://learn.microsoft.com/en-us/vcpkg/users/config-environment
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain")
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")

#
project ("opengl-suffering" CXX C)

#
# message(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 

#
# TODO: https://github.com/libsdl-org/SDL_image
# TODO: add https://github.com/libsdl-org
find_package(glfw3 CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
#
SET(LIBRARIES OpenGL::GL GLEW::GLEW glfw SDL3::SDL3 glm::glm assimp::assimp Freetype::Freetype)

#source to this project's executable.
add_subdirectory(src)

#tests and targets.
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()


# https://wiki.libsdl.org/SDL3/QuickReference
