project("4-2-textures_combined") 
add_executable("4-2-textures_combined_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-2-textures_combined_executable" PRIVATE "${LIBRARIES}")

configure_file(4.2.texture.fs 4.2.texture.fs COPYONLY)
configure_file(4.2.texture.vs 4.2.texture.vs COPYONLY)
