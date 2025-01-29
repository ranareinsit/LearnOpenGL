project("4-3-lighting_maps_exercise2")
add_executable("4-3-lighting_maps_exercise2_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-3-lighting_maps_exercise2_executable" PRIVATE "${LIBRARIES}")

configure_file(4.3.lighting_maps.fs 4.3.lighting_maps.fs COPYONLY)
configure_file(4.3.lighting_maps.vs 4.3.lighting_maps.vs COPYONLY)
configure_file(4.3.light_cube.fs 4.3.light_cube.fs COPYONLY)
configure_file(4.3.light_cube.vs 4.3.light_cube.vs COPYONLY)
