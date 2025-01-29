project("4-4-lighting_maps_exercise4")
add_executable("4-4-lighting_maps_exercise4_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-4-lighting_maps_exercise4_executable" PRIVATE "${LIBRARIES}")

configure_file(4.4.lighting_maps.fs 4.4.lighting_maps.fs COPYONLY)
configure_file(4.4.lighting_maps.vs 4.4.lighting_maps.vs COPYONLY)
configure_file(4.4.light_cube.fs 4.4.light_cube.fs COPYONLY)
configure_file(4.4.light_cube.vs 4.4.light_cube.vs COPYONLY)
