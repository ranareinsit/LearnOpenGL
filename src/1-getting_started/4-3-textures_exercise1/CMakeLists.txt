project("4-3-textures_exercise1") 
add_executable("4-3-textures_exercise1_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("4-3-textures_exercise1_executable" PRIVATE "${LIBRARIES}")

configure_file(4.3.texture.fs 4.3.texture.fs COPYONLY)
configure_file(4.3.texture.vs 4.3.texture.vs COPYONLY)
