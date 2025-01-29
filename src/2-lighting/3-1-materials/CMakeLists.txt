project("3-1-materials")
add_executable("3-1-materials_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("3-1-materials_executable" PRIVATE "${LIBRARIES}")

configure_file(3.1.light_cube.fs 3.1.light_cube.fs COPYONLY)
configure_file(3.1.light_cube.vs 3.1.light_cube.vs COPYONLY)
configure_file(3.1.materials.fs 3.1.materials.fs COPYONLY)
configure_file(3.1.materials.vs 3.1.materials.vs COPYONLY)
