project("8-2-deferred_shading_volumes")
add_executable("8-2-deferred_shading_volumes_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("8-2-deferred_shading_volumes_executable" PRIVATE "${LIBRARIES}")
configure_file(8.2.deferred_light_box.fs 8.2.deferred_light_box.fs COPYONLY)
configure_file(8.2.deferred_light_box.vs 8.2.deferred_light_box.vs COPYONLY)
configure_file(8.2.deferred_shading.fs 8.2.deferred_shading.fs COPYONLY)
configure_file(8.2.deferred_shading.vs 8.2.deferred_shading.vs COPYONLY)
configure_file(8.2.g_buffer.fs 8.2.g_buffer.fs COPYONLY)
configure_file(8.2.g_buffer.vs 8.2.g_buffer.vs COPYONLY)