# ifndef PLAYER_H
# define PLAYER_H

# include "Arkanoid.h"

# include "level.h"


typedef struct
{
    ui_vec2d pos;
    uint loss;
    uint dir;
    uint speed;

    uint weight;
}
Player;


void init_player ();
void move_player ();


# endif // PLAYER