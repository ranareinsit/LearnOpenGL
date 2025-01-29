project("terrain_gpu_dist")
add_executable("terrain_gpu_dist_executable" "main.cpp")
include_directories("../../../../includes")
target_link_libraries("terrain_gpu_dist_executable" PRIVATE "${LIBRARIES}")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/heightmaps )

configure_file(heightmaps/iceland_heightmap.png ${CMAKE_CURRENT_BINARY_DIR}/heightmaps/iceland_heightmap.png COPYONLY)
configure_file(heightmaps/river_heightmap.png ${CMAKE_CURRENT_BINARY_DIR}/heightmaps/river_heightmap.png COPYONLY)
configure_file(heightmaps/river2_heightmap.png ${CMAKE_CURRENT_BINARY_DIR}/heightmaps/river2_heightmap.png COPYONLY)

configure_file(8.3.gpuheight.fs 8.3.gpuheight.fs COPYONLY)
configure_file(8.3.gpuheight.tcs 8.3.gpuheight.tcs COPYONLY)
configure_file(8.3.gpuheight.tes 8.3.gpuheight.tes COPYONLY)
configure_file(8.3.gpuheight.vs 8.3.gpuheight.vs COPYONLY)
