project("1-model_loading")
add_executable("1-model_loading_executable" "main.cpp")
include_directories("../../includes")
target_link_libraries("1-model_loading_executable" PRIVATE "${LIBRARIES}")

configure_file(1.model_loading.fs 1.model_loading.fs COPYONLY)
configure_file(1.model_loading.vs 1.model_loading.vs COPYONLY)
