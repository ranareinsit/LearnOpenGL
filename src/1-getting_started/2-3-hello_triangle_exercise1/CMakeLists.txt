project("2-3-hello_triangle_exercise1") 
add_executable("2-3-hello_triangle_exercise1_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("2-3-hello_triangle_exercise1_executable" PRIVATE "${LIBRARIES}")
