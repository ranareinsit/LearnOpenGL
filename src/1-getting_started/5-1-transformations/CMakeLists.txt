project("5-1-transformations") 
add_executable("5-1-transformations_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-1-transformations_executable" PRIVATE "${LIBRARIES}")

configure_file(5.1.transform.fs 5.1.transform.fs COPYONLY)
configure_file(5.1.transform.vs 5.1.transform.vs COPYONLY)
