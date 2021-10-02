# ifndef CONSOLE_H
# define CONSOLE_H


# include "Arkanoid.h"


typedef struct
{
    HANDLE std_output_handle;
    COORD cursor_zero_pos;
}
ConsoleDescriptor;


typedef string OutputBuffer;
typedef size_t_vec2d OutputBufferSize;


void init_console ();
void init_console_output_buffer ();

void clear_console ();
void show_output_buffer ();


void set_console_cursor_position (HANDLE std_buffer_handle, COORD position);


# endif // CONSOLE