project("7-5-camera_exercise1") 
add_executable("7-5-camera_exercise1_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("7-5-camera_exercise1_executable" PRIVATE "${LIBRARIES}")

configure_file(7.5.camera.fs 7.5.camera.fs COPYONLY)
configure_file(7.5.camera.vs 7.5.camera.vs COPYONLY)
