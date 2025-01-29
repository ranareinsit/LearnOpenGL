project("4-2-lighting_maps_specular_map")
add_executable("4-2-lighting_maps_specular_map_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-2-lighting_maps_specular_map_executable" PRIVATE "${LIBRARIES}")

configure_file(4.2.lighting_maps.fs 4.2.lighting_maps.fs COPYONLY)
configure_file(4.2.lighting_maps.vs 4.2.lighting_maps.vs COPYONLY)
configure_file(4.2.light_cube.fs 4.2.light_cube.fs COPYONLY)
configure_file(4.2.light_cube.vs 4.2.light_cube.vs COPYONLY)
