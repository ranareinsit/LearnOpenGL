project("8-1-deferred_shading")
add_executable("8-1-deferred_shading_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("8-1-deferred_shading_executable" PRIVATE "${LIBRARIES}")
configure_file(8.1.deferred_light_box.fs 8.1.deferred_light_box.fs COPYONLY)
configure_file(8.1.deferred_light_box.vs 8.1.deferred_light_box.vs COPYONLY)
configure_file(8.1.deferred_shading.fs 8.1.deferred_shading.fs COPYONLY)
configure_file(8.1.deferred_shading.vs 8.1.deferred_shading.vs COPYONLY)
configure_file(8.1.fbo_debug.fs 8.1.fbo_debug.fs COPYONLY)
configure_file(8.1.fbo_debug.vs 8.1.fbo_debug.vs COPYONLY)
configure_file(8.1.g_buffer.fs 8.1.g_buffer.fs COPYONLY)
configure_file(8.1.g_buffer.vs 8.1.g_buffer.vs COPYONLY)