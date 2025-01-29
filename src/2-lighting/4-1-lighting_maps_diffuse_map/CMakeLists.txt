project("4-1-lighting_maps_diffuse_map")
add_executable("4-1-lighting_maps_diffuse_map_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-1-lighting_maps_diffuse_map_executable" PRIVATE "${LIBRARIES}")

configure_file(4.1.lighting_maps.fs 4.1.lighting_maps.fs COPYONLY)
configure_file(4.1.lighting_maps.vs 4.1.lighting_maps.vs COPYONLY)
configure_file(4.1.light_cube.fs 4.1.light_cube.fs COPYONLY)
configure_file(4.1.light_cube.vs 4.1.light_cube.vs COPYONLY)
