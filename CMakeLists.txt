cmake_minimum_required (VERSION 3.8)

project (Arkanoid LANGUAGES C)

set (SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set (RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set (COMMON_DIR "${CMAKE_SOURCE_DIR}/common")

# configure_file (
# 	"${COMMON_DIR}/config.h.in" 
# 	"${SOURCE_DIR}/config.h"
# 	ESCAPE_QUOTES @ONLY
# )

add_library (lib_arkanoid OBJECT

	"src/Arkanoid.h"

	"src/level.c"
	"src/level.h"

	"src/console.h"
	"src/console.c" 

	"src/utils.h" 
	"src/utils.c"

	"src/player.h"
	"src/player.c"
	
	"src/ball.h"
	"src/ball.c"
  
	"src/game.h"
	"src/game.c"
 
	"src/globals.h" 
	"src/globals.c" 
	
	"src/config.h"
)

add_executable (Arkanoid "src/Arkanoid.c")
target_link_libraries (Arkanoid PRIVATE lib_arkanoid)
