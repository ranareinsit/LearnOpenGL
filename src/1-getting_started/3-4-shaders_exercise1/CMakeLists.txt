project("3-4-shaders_exercise1") 
add_executable("3-4-shaders_exercise1_executable" "main.cpp")
include_directories(${DEPS_M})
target_link_libraries("3-4-shaders_exercise1_executable" PRIVATE "${LIBRARIES}")

configure_file(3.4.shader.fs 3.4.shader.fs COPYONLY)
configure_file(3.4.shader.vs 3.4.shader.vs COPYONLY)
