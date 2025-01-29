project("3-2-shaders_interpolation") 
add_executable("3-2-shaders_interpolation_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("3-2-shaders_interpolation_executable" PRIVATE "${LIBRARIES}")
