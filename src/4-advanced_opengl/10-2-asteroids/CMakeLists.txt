project("10-2-asteroids")
add_executable("10-2-asteroids_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("10-2-asteroids_executable" PRIVATE "${LIBRARIES}")
configure_file(10.2.instancing.fs 10.2.instancing.fs COPYONLY)
configure_file(10.2.instancing.vs 10.2.instancing.vs COPYONLY)