project("1-2-hello_window_clear") 
add_executable("1-2-hello_window_clear_executable" "main.cpp") 
include_directories("../../includes")
target_link_libraries("1-2-hello_window_clear_executable" PRIVATE "${LIBRARIES}" ) 
 