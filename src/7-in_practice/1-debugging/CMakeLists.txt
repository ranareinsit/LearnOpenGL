project("1-debugging")
add_executable("1-debugging_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("1-debugging_executable" PRIVATE "${LIBRARIES}")
configure_file(debugging.fs debugging.fs COPYONLY)
configure_file(debugging.vs debugging.vs COPYONLY)