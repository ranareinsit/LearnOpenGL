project("2-1-basic_lighting_diffuse")
add_executable("2-1-basic_lighting_diffuse_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-1-basic_lighting_diffuse_executable" PRIVATE "${LIBRARIES}")

configure_file(2.1.basic_lighting.fs 2.1.basic_lighting.fs COPYONLY)
configure_file(2.1.basic_lighting.vs 2.1.basic_lighting.vs COPYONLY)
configure_file(2.1.light_cube.fs 2.1.light_cube.fs COPYONLY)
configure_file(2.1.light_cube.vs 2.1.light_cube.vs COPYONLY)
