project("5-1-light_casters_directional")
add_executable("5-1-light_casters_directional_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-1-light_casters_directional_executable" PRIVATE "${LIBRARIES}")

configure_file(5.1.light_casters.fs 5.1.light_casters.fs COPYONLY)
configure_file(5.1.light_casters.vs 5.1.light_casters.vs COPYONLY)
configure_file(5.1.light_cube.fs 5.1.light_cube.fs COPYONLY)
configure_file(5.1.light_cube.vs 5.1.light_cube.vs COPYONLY)
