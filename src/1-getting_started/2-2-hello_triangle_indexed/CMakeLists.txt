project("2-2-hello_triangle_indexed") 
add_executable("2-2-hello_triangle_indexed_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-2-hello_triangle_indexed_executable" PRIVATE "${LIBRARIES}")
