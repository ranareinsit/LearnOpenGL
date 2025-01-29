project("4-6-textures_exercise4") 
add_executable("4-6-textures_exercise4_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-6-textures_exercise4_executable" PRIVATE "${LIBRARIES}")

configure_file(4.6.texture.fs 4.6.texture.fs COPYONLY)
configure_file(4.6.texture.vs 4.6.texture.vs COPYONLY)
