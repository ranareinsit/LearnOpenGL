project("6-2-coordinate_systems_depth") 
add_executable("6-2-coordinate_systems_depth_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("6-2-coordinate_systems_depth_executable" PRIVATE "${LIBRARIES}")

configure_file(6.2.coordinate_systems.fs 6.2.coordinate_systems.fs COPYONLY)
configure_file(6.2.coordinate_systems.vs 6.2.coordinate_systems.vs COPYONLY)
