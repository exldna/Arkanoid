# include "game.h"

# include "level.h"
# include "player.h"
# include "ball.h"

extern GameState game_state;


void init_game ()
{
	game_state.is_running = true;
	game_state.is_playing = false;
	game_state.level_index = 0;
}


void restart_game (uint level_i)
{
	load_level (level_i);
	init_player ();	
	init_ball ();
	init_game ();

	game_state.level_index = level_i;
}