project("4-dsa")
add_executable("4-dsa_executable" "main.cpp")
include_directories("../../../includes")
target_link_libraries("4-dsa_executable" PRIVATE "${LIBRARIES}")
