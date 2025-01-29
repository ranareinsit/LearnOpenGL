project("6-3-coordinate_systems_multiple") 
add_executable("6-3-coordinate_systems_multiple_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("6-3-coordinate_systems_multiple_executable" PRIVATE "${LIBRARIES}")

configure_file(6.3.coordinate_systems.fs 6.3.coordinate_systems.fs COPYONLY)
configure_file(6.3.coordinate_systems.vs 6.3.coordinate_systems.vs COPYONLY)
