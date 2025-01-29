project("7-6-camera_exercise2") 
add_executable("7-6-camera_exercise2_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("7-6-camera_exercise2_executable" PRIVATE "${LIBRARIES}")

configure_file("7.6.camera.fs"  7.6.camera.fs COPYONLY)
configure_file("7.6.camera.vs"  7.6.camera.vs COPYONLY)
