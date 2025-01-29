project("2-2-basic_lighting_specular")
add_executable("2-2-basic_lighting_specular_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-2-basic_lighting_specular_executable" PRIVATE "${LIBRARIES}")

configure_file(2.2.basic_lighting.fs 2.2.basic_lighting.fs COPYONLY)
configure_file(2.2.basic_lighting.vs 2.2.basic_lighting.vs COPYONLY)
configure_file(2.2.light_cube.fs 2.2.light_cube.fs COPYONLY)
configure_file(2.2.light_cube.vs 2.2.light_cube.vs COPYONLY)
