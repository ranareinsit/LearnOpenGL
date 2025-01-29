project("3-6-shaders_exercise3") 
add_executable("3-6-shaders_exercise3_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("3-6-shaders_exercise3_executable" PRIVATE "${LIBRARIES}")

configure_file(3.6.shader.fs 3.6.shader.fs COPYONLY)
configure_file(3.6.shader.vs 3.6.shader.vs COPYONLY)
