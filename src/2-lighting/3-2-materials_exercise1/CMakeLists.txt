project("3-2-materials_exercise1")
add_executable("3-2-materials_exercise1_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("3-2-materials_exercise1_executable" PRIVATE "${LIBRARIES}")

configure_file(3.2.light_cube.fs 3.2.light_cube.fs COPYONLY)
configure_file(3.2.light_cube.vs 3.2.light_cube.vs COPYONLY)
configure_file(3.2.materials.fs 3.2.materials.fs COPYONLY)
configure_file(3.2.materials.vs 3.2.materials.vs COPYONLY)
