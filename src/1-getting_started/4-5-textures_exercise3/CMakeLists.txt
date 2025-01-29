project("4-5-textures_exercise3") 
add_executable("4-5-textures_exercise3_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-5-textures_exercise3_executable" PRIVATE "${LIBRARIES}" ) 

configure_file(4.5.texture.fs 4.5.texture.fs COPYONLY)
configure_file(4.5.texture.vs 4.5.texture.vs COPYONLY)
