project("5-2-framebuffers_exercise1")
add_executable("5-2-framebuffers_exercise1_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("5-2-framebuffers_exercise1_executable" PRIVATE "${LIBRARIES}")
configure_file(5.2.framebuffers.fs 5.2.framebuffers.fs COPYONLY)
configure_file(5.2.framebuffers.vs 5.2.framebuffers.vs COPYONLY)
configure_file(5.2.framebuffers_screen.fs 5.2.framebuffers_screen.fs COPYONLY)
configure_file(5.2.framebuffers_screen.vs 5.2.framebuffers_screen.vs COPYONLY)