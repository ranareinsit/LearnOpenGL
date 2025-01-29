project("3-1-shaders_uniform") 
add_executable("3-1-shaders_uniform_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("3-1-shaders_uniform_executable" PRIVATE "${LIBRARIES}")
