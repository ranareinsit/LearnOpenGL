project("3-5-shaders_exercise2")
include_directories("../../includes")
add_executable("3-5-shaders_exercise2_executable" "main.cpp")
target_link_libraries("3-5-shaders_exercise2_executable" PRIVATE "${LIBRARIES}")

configure_file(3.5.shader.fs 3.5.shader.fs COPYONLY)
configure_file(3.5.shader.vs 3.5.shader.vs COPYONLY)
