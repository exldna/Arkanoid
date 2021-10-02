# include "ball.h"
# include "player.h"
# include "level.h"
# include "game.h"

# include <math.h>


extern LevelSize LEVEL_BUFFER_SIZE;

extern Level level;
extern Player player;
extern Ball ball;


void init_ball ()
{
    ball.loss = 0;
    ball.speed = 15;

    ball.dir.x =  -1;
    ball.dir.y = -1;
}


void compute_ball_collisions ()
{
    // получаем следующую позицию м€ча
    ui_vec2d next_pos = ball.pos;

    next_pos.x += ball.dir.x;
    next_pos.y += ball.dir.y;

    // обрабатываем коллизию с платформой
    if (next_pos.y == player.pos.y &&
        next_pos.x >= player.pos.x &&
        next_pos.x <  player.pos.x + player.weight
        )
    {
        ball.dir.y = -1;
    }

    // получаем индекс в level на следующую позицию м€ча
    size_t next_i_x  = get_index_in_buffer (next_pos.x, ball.pos.y, LEVEL_BUFFER_SIZE);
    size_t next_i_y  = get_index_in_buffer (ball.pos.x, next_pos.y, LEVEL_BUFFER_SIZE);
    size_t next_i_xy = get_index_in_buffer (next_pos.x, next_pos.y, LEVEL_BUFFER_SIZE);

    if (check_cell (next_i_x) || check_cell (next_i_y))
    {
        if (check_cell (next_i_x))
        {
            ball.dir.x = -ball.dir.x;
            break_block (next_i_x);
        }
        if (check_cell (next_i_y))
        {
            ball.dir.y = -ball.dir.y;
            break_block (next_i_y);
        }
    }
    else if (check_cell (next_i_xy))
    {
        ball.dir.x = -ball.dir.x;
        ball.dir.y = -ball.dir.y;
        break_block (next_i_xy);
    }
}


void move_ball ()
{
    // считаем кол-во update-ов
    ++ball.loss;
    // если пора передвинуть м€ч
    if (ball.loss >= ball.speed)
    {
        compute_ball_collisions ();
        // двигаем м€ч
        ball.pos.x += ball.dir.x;
        ball.pos.y += ball.dir.y;
        
        ball.loss -= ball.speed;
    }
}