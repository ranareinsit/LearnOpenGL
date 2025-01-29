project("6-4-coordinate_systems_exercise3") 
add_executable("6-4-coordinate_systems_exercise3_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("6-4-coordinate_systems_exercise3_executable" PRIVATE "${LIBRARIES}")

configure_file(6.4.coordinate_systems.fs 6.4.coordinate_systems.fs COPYONLY)
configure_file(6.4.coordinate_systems.vs 6.4.coordinate_systems.vs COPYONLY)
