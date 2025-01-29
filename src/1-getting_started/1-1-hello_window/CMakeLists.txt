project("1-1-hello_window")
add_executable("1-1-hello_window_executable" main.cpp)
include_directories("../../includes")
target_link_libraries("1-1-hello_window_executable" PRIVATE "${LIBRARIES}") 
