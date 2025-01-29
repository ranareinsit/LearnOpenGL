project("5-4-light_casters_spot_soft")
add_executable("5-4-light_casters_spot_soft_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-4-light_casters_spot_soft_executable" PRIVATE "${LIBRARIES}")

configure_file(5.4.light_casters.fs 5.4.light_casters.fs COPYONLY)
configure_file(5.4.light_casters.vs 5.4.light_casters.vs COPYONLY)
configure_file(5.4.light_cube.fs 5.4.light_cube.fs COPYONLY)
configure_file(5.4.light_cube.vs 5.4.light_cube.vs COPYONLY)
