# ifndef BALL_H
# define BALL_H


# include "Arkanoid.h"


typedef struct
{
    ui_vec2d pos;
    vec2d dir;

    uint loss;
    uint speed;
}
Ball;

void init_ball ();
void move_ball ();

# endif // BALL