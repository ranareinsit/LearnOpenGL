project("7-3-camera_mouse_zoom") 
add_executable("7-3-camera_mouse_zoom_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("7-3-camera_mouse_zoom_executable" PRIVATE "${LIBRARIES}")

configure_file(7.3.camera.fs 7.3.camera.fs COPYONLY)
configure_file(7.3.camera.vs 7.3.camera.vs COPYONLY)
