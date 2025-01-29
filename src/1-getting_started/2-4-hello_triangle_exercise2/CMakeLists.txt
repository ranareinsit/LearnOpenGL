project("2-4-hello_triangle_exercise2") 
add_executable("2-4-hello_triangle_exercise2_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-4-hello_triangle_exercise2_executable" PRIVATE "${LIBRARIES}")
