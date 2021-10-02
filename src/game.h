# ifndef GAME_H
# define GAME_H


# include "Arkanoid.h"


typedef struct
{
	bool is_running;
	bool is_playing;

	ushort level_index;
} 
GameState;


void init_game ();
void restart_game (uint level_i);

# endif // GAME