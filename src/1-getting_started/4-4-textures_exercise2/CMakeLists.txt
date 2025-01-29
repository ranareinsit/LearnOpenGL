project("4-4-textures_exercise2") 
add_executable("4-4-textures_exercise2_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-4-textures_exercise2_executable" PRIVATE "${LIBRARIES}")

configure_file(4.4.texture.fs 4.4.texture.fs COPYONLY)
configure_file(4.4.texture.vs 4.4.texture.vs COPYONLY)
