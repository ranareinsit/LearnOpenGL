project("4-1-textures") 
add_executable("4-1-textures_executable" "main.cpp") 
include_directories("../../includes")
target_link_libraries("4-1-textures_executable" PRIVATE "${LIBRARIES}")

configure_file(4.1.texture.fs 4.1.texture.fs COPYONLY)
configure_file(4.1.texture.vs 4.1.texture.vs COPYONLY)
