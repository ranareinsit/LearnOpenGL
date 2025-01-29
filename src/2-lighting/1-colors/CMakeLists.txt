project("1-colors")
add_executable("1-colors_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("1-colors_executable" PRIVATE "${LIBRARIES}")

configure_file(1.colors.fs 1.colors.fs COPYONLY)
configure_file(1.colors.vs 1.colors.vs COPYONLY)
configure_file(1.light_cube.fs 1.light_cube.fs COPYONLY)
configure_file(1.light_cube.vs 1.light_cube.vs COPYONLY)
