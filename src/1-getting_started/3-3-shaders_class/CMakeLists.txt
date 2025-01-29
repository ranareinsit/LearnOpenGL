project("3-3-shaders_class")
add_executable("3-3-shaders_class_executable" "main.cpp")
include_directories(${DEPS_M})
target_link_libraries("3-3-shaders_class_executable" PRIVATE "${LIBRARIES}")

configure_file(3.3.shader.fs 3.3.shader.fs COPYONLY)
configure_file(3.3.shader.vs 3.3.shader.vs COPYONLY)
