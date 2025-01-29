project("3-2d_game")
add_executable("3-2d_game_executable" 
	program.cpp
	ball_object.cpp
	ball_object.h
	CMakeLists.txt
	game.cpp
	game.h
	game_level.cpp
	game_level.h
	game_object.cpp
	game_object.h
	particle_generator.cpp
	particle_generator.h
	post_processor.cpp
	post_processor.h
	power_up.h
	resource_manager.cpp
	resource_manager.h
	shader.cpp
	shader.h
	sprite_renderer.cpp
	sprite_renderer.h
	stb_image.cpp
	texture.cpp
	texture.h
	text_renderer.cpp
	text_renderer.h
)
include_directories("../../../includes")
target_link_libraries("3-2d_game_executable" PRIVATE "${LIBRARIES}")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/levels)

configure_file(levels/one.lvl ${CMAKE_CURRENT_BINARY_DIR}/levels/one.lvl COPYONLY)
configure_file(levels/two.lvl ${CMAKE_CURRENT_BINARY_DIR}/levels/two.lvl COPYONLY)
configure_file(levels/three.lvl ${CMAKE_CURRENT_BINARY_DIR}/levels/three.lvl COPYONLY)
configure_file(levels/four.lvl ${CMAKE_CURRENT_BINARY_DIR}/levels/four.lvl COPYONLY)

configure_file(particle.fs particle.fs COPYONLY)
configure_file(particle.vs particle.vs COPYONLY)
configure_file(post_processing.fs post_processing.fs COPYONLY)
configure_file(post_processing.vs post_processing.vs COPYONLY)
configure_file(sprite.fs sprite.fs COPYONLY)
configure_file(sprite.vs sprite.vs COPYONLY)
configure_file(text_2d.fs text_2d.fs COPYONLY)
configure_file(text_2d.vs text_2d.vs COPYONLY)
