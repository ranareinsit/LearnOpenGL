project("6-1-coordinate_systems") 
add_executable("6-1-coordinate_systems_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("6-1-coordinate_systems_executable" PRIVATE "${LIBRARIES}")

configure_file(6.1.coordinate_systems.fs 6.1.coordinate_systems.fs COPYONLY)
configure_file(6.1.coordinate_systems.vs 6.1.coordinate_systems.vs COPYONLY)
