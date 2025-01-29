project("2-5-hello_triangle_exercise3") 
add_executable("2-5-hello_triangle_exercise3_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-5-hello_triangle_exercise3_executable" PRIVATE "${LIBRARIES}")
