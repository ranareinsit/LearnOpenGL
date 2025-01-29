project("5-3-transformations_exercise2") 
add_executable("5-3-transformations_exercise2_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-3-transformations_exercise2_executable" PRIVATE "${LIBRARIES}")

configure_file(5.3.transform.fs 5.3.transform.fs COPYONLY)
configure_file(5.3.transform.vs 5.3.transform.vs COPYONLY)
