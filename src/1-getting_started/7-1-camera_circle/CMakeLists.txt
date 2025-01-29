project("7-1-camera_circle") 
add_executable("7-1-camera_circle_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("7-1-camera_circle_executable" PRIVATE "${LIBRARIES}")

configure_file(7.1.camera.fs 7.1.camera.fs COPYONLY)
configure_file(7.1.camera.vs 7.1.camera.vs COPYONLY)
