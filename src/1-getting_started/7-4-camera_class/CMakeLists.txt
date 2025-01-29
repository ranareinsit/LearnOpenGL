project("7-4-camera_class") 
add_executable("7-4-camera_class_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("7-4-camera_class_executable" PRIVATE "${LIBRARIES}")

configure_file(7.4.camera.fs 7.4.camera.fs COPYONLY)
configure_file(7.4.camera.vs 7.4.camera.vs COPYONLY)
