project("2-4-basic_lighting_exercise2")
add_executable("2-4-basic_lighting_exercise2_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-4-basic_lighting_exercise2_executable" PRIVATE "${LIBRARIES}")

configure_file(2.4.basic_lighting.fs 2.4.basic_lighting.fs COPYONLY)
configure_file(2.4.basic_lighting.vs 2.4.basic_lighting.vs COPYONLY)
configure_file(2.4.light_cube.fs 2.4.light_cube.fs COPYONLY)
configure_file(2.4.light_cube.vs 2.4.light_cube.vs COPYONLY)
