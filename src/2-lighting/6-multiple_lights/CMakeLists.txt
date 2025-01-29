project("6-multiple_lights")
add_executable("6-multiple_lights_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("6-multiple_lights_executable" PRIVATE "${LIBRARIES}")

configure_file(6.light_cube.fs 6.light_cube.fs COPYONLY)
configure_file(6.light_cube.vs 6.light_cube.vs COPYONLY)
configure_file(6.multiple_lights.fs 6.multiple_lights.fs COPYONLY)
configure_file(6.multiple_lights.vs 6.multiple_lights.vs COPYONLY)
