# include "globals.h"

# include "console.h"
# include "level.h"


OutputBufferSize WINDOW_SIZE;

size_t_vec2d CONSOLE_BUFFER_SIZE;
size_t CONSOLE_BUFFER_LEN;

LevelSize LEVEL_BUFFER_SIZE;
size_t LEVEL_BUFFER_LEN;
size_t_vec2d LEVEL_OFFSET;
size_t INFO_BUFFER;

const ulong MAX_UPD = 200;
long UPD_DUR;


void init_globals ()
{
	UPD_DUR = CLOCKS_PER_SEC / MAX_UPD;

	LEVEL_BUFFER_SIZE.x = 50;
	LEVEL_BUFFER_SIZE.y = 21;

	LEVEL_OFFSET.x = 1;
	LEVEL_OFFSET.y = 1;

	INFO_BUFFER = 0;

	// line: -- ... --** ... **0 | -- : OFFSET, ** : VIEW, 0 : end-line char
	WINDOW_SIZE.x = LEVEL_BUFFER_SIZE.x + LEVEL_OFFSET.x + INFO_BUFFER;
	WINDOW_SIZE.y = LEVEL_BUFFER_SIZE.y + LEVEL_OFFSET.y;

	CONSOLE_BUFFER_SIZE.x = WINDOW_SIZE.x + 1;
	CONSOLE_BUFFER_SIZE.y = WINDOW_SIZE.y;

	CONSOLE_BUFFER_LEN = sizeof (char) * CONSOLE_BUFFER_SIZE.x * CONSOLE_BUFFER_SIZE.y;
	LEVEL_BUFFER_LEN = sizeof (CellType) * LEVEL_BUFFER_SIZE.x * LEVEL_BUFFER_SIZE.y;
}