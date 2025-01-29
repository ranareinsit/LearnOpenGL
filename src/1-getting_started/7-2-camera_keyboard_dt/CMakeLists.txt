project("7-2-camera_keyboard_dt") 
add_executable("7-2-camera_keyboard_dt_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("7-2-camera_keyboard_dt_executable" PRIVATE "${LIBRARIES}")

configure_file(7.2.camera.fs 7.2.camera.fs COPYONLY)
configure_file(7.2.camera.vs 7.2.camera.vs COPYONLY)
