# include "Arkanoid.h"

# include "console.h"

# include "game.h"
# include "level.h"
# include "player.h"
# include "ball.h"


extern ulong UPD_DUR;

extern size_t_vec2d CONSOLE_BUFFER_SIZE;
extern size_t COSNOLE_BUFFER_LEN;

extern LevelSize LEVEL_BUFFER_SIZE;
extern size_t_vec2d LEVEL_OFFSET;


GameState game_state;
Level level;
volatile Player player;
volatile Ball ball;

volatile OutputBuffer console_output_buffer;
ConsoleDescriptor console_descriptor;


void initialize ()
{
	init_globals ();

	init_console ();
	init_console_output_buffer ();

	init_level ();
}


void finalize ()
{
	// освобождаем захваченные указатели
	free (level);
	free (console_output_buffer);
}


void update ()
{
	move_player ();

	if (!game_state.is_playing)
	{
		// устанавливаем мяч на платформе
		ball.pos.x = player.pos.x + player.weight / 2;
		ball.pos.y = player.pos.y - 1;
	}
	else
	{
		// если мяч вылетел за границу поля
		if (ball.pos.y == LEVEL_BUFFER_SIZE.y - 1)
		{
			restart_game (game_state.level_index);
			return;
		}

		move_ball ();
	}
}

void draw ()
{
	size_t out_it, lvl_it;

	char curr_char;
	CellType curr_cell;

	// пробегаем по всему игровому полю
	for (size_t y = 0; y < LEVEL_BUFFER_SIZE.y; ++y)
	{
		for (size_t x = 0; x < LEVEL_BUFFER_SIZE.x; ++x)
		{
			// если в этой позиции находится игрок - рисуем игрока
			if (x >= player.pos.x && 
				x <  player.pos.x + player.weight &&
				y == player.pos.y)
			{
				curr_char = 223;
			}
			// если мяч - рисуем мяч
			else if (x == ball.pos.x && 
					 y == ball.pos.y)
			{
				curr_char = 174;
			}
			else // иначе - отрисовываем клетку поля
			{
				lvl_it = get_index_in_buffer (x, y, LEVEL_BUFFER_SIZE);
				
				curr_cell = level[lvl_it];
				
				switch (curr_cell)
				{
					case wall:
						curr_char = 219;
						break;
					case space:
						curr_char = ' ';
						break;
					case block_0:
						curr_char = 176;
						break;
					case block_1:
						curr_char = 177;
						break;
					case block_2:
						curr_char = 178;
						break;
					default:
						curr_char = '.';
				};
			}
			// рисуем клетку
			out_it = get_index_in_buffer (
				x + LEVEL_OFFSET.x,
				y + LEVEL_OFFSET.y,
				CONSOLE_BUFFER_SIZE
			);

			console_output_buffer[out_it] = curr_char;
		}
	}

	show_output_buffer ();
}

void input ()
{
	// exit
	if (GetKeyState (VK_ESCAPE) & 0x8000)
	{
		game_state.is_running = false;
	}
	// start game
	if (!game_state.is_playing && GetKeyState (0x57) & 0x8000)
	{
		game_state.is_playing = true;
	}
	// move player left
	if (player.dir != -1 && GetKeyState (VK_LEFT) & 0x8000)
	{
		player.dir = -1;
	}
	// move player right
	if (player.dir != 1 && GetKeyState (VK_RIGHT) & 0x8000)
	{
		player.dir = 1;
	}
}


int main ()
{
	initialize ();

	uint level_i = 0;
	printf ("choose level (1, 2 or 3): ");
	scanf ("%u", &level_i);

	restart_game (level_i - 1);

	clock_t curr_time, last_time = clock(), delta_time = 0;
	bool is_update;

	while (game_state.is_running == true)
	{
		is_update = false;

		curr_time = clock ();
		delta_time += curr_time - last_time;

		input ();

		while (delta_time >= UPD_DUR)
		{
			update ();

			delta_time -= UPD_DUR;
			if (!is_update)
			{
				is_update = true;
			}
		}

		if (is_update)
		{
			draw ();
		}

		last_time = curr_time;

	}

	finalize ();

	return 0;
}