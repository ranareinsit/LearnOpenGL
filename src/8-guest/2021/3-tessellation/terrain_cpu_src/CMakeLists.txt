project("terrain_cpu_src")
add_executable("terrain_cpu_src_executable" "main.cpp")
include_directories("../../../../includes")
target_link_libraries("terrain_cpu_src_executable" PRIVATE "${LIBRARIES}")
configure_file(8.3.cpuheight.fs 8.3.cpuheight.fs COPYONLY)
configure_file(8.3.cpuheight.vs 8.3.cpuheight.vs COPYONLY)


file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/heightmaps )

configure_file(heightmaps/iceland_heightmap.png ${CMAKE_CURRENT_BINARY_DIR}/heightmaps/iceland_heightmap.png COPYONLY)
configure_file(heightmaps/river_heightmap.png ${CMAKE_CURRENT_BINARY_DIR}/heightmaps/river_heightmap.png COPYONLY)
configure_file(heightmaps/river2_heightmap.png ${CMAKE_CURRENT_BINARY_DIR}/heightmaps/river2_heightmap.png COPYONLY)

configure_file(8.3.cpuheight.fs 8.3.cpuheight.fs COPYONLY)
configure_file(8.3.cpuheight.vs 8.3.cpuheight.vs COPYONLY)
