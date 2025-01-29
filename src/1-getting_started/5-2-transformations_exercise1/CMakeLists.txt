project("5-2-transformations_exercise1") 
add_executable("5-2-transformations_exercise1_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-2-transformations_exercise1_executable" PRIVATE "${LIBRARIES}")

configure_file(5.2.transform.fs 5.2.transform.fs COPYONLY)
configure_file(5.2.transform.vs 5.2.transform.vs COPYONLY)
