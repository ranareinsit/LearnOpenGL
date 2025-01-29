project("2-1-hello_triangle") 
add_executable("2-1-hello_triangle_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-1-hello_triangle_executable" PRIVATE "${LIBRARIES}" ) 
 