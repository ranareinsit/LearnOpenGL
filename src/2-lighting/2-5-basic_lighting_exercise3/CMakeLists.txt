project("2-5-basic_lighting_exercise3")
add_executable("2-5-basic_lighting_exercise3_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-5-basic_lighting_exercise3_executable" PRIVATE "${LIBRARIES}")

configure_file(2.5.basic_lighting.fs 2.5.basic_lighting.fs COPYONLY)
configure_file(2.5.basic_lighting.vs 2.5.basic_lighting.vs COPYONLY)
configure_file(2.5.light_cube.fs 2.5.light_cube.fs COPYONLY)
configure_file(2.5.light_cube.vs 2.5.light_cube.vs COPYONLY)
