project("5-2-light_casters_point")
add_executable("5-2-light_casters_point_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-2-light_casters_point_executable" PRIVATE "${LIBRARIES}")

configure_file(5.2.light_casters.fs 5.2.light_casters.fs COPYONLY)
configure_file(5.2.light_casters.vs 5.2.light_casters.vs COPYONLY)
configure_file(5.2.light_cube.fs 5.2.light_cube.fs COPYONLY)
configure_file(5.2.light_cube.vs 5.2.light_cube.vs COPYONLY)
