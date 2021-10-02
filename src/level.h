# ifndef LEVEL_H
# define LEVEL_H

# include "Arkanoid.h"


typedef enum
{
    wall,
    space,

    block_0,
    block_1,
    block_2
}
CellType;


typedef size_t_vec2d LevelSize;
typedef CellType* Level;


void init_level ();
void load_level (size_t i);
void break_block (size_t i);
bool check_cell (size_t i);


# endif // LEVEL