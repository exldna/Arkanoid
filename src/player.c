# include "player.h"

# include <math.h>


extern Player player;

extern LevelSize LEVEL_BUFFER_SIZE;


void init_player ()
{
    player.weight = 7;
    player.speed = 5;

    player.pos.x = (LEVEL_BUFFER_SIZE.x - player.weight) / 2;
    player.pos.y = LEVEL_BUFFER_SIZE.y - 2;

    player.loss = 0;
}


void compute_player_collisions ()
{
    uint new_x = player.pos.x + player.dir;

    // если выходим за границы карты
    if (!(new_x > 0 && new_x < LEVEL_BUFFER_SIZE.x - player.weight))
    {
        player.dir = 0;
    }
}


void move_player ()
{
    ++player.loss;

    if (player.loss >= player.speed)
    {
        compute_player_collisions ();
        player.pos.x += player.dir;

        player.dir = 0;
        player.loss -= player.speed;
    }
}
