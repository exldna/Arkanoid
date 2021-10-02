# ifndef UTILS_H
# define UTILS_H


// std types

typedef unsigned uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

typedef char* string;


// shapes

typedef struct
{
	int x;
	int y;
}
i_vec2d;

typedef struct 
{
	uint x;
	uint y;
}
ui_vec2d;

typedef struct
{
	size_t x;
	size_t y;
}
size_t_vec2d;

typedef struct
{
	float x;
	float y;
}
f_vec2d;

typedef i_vec2d vec2d;


typedef struct
{
	ui_vec2d pos;
	ui_vec2d size;
}
Rect;


// functools

size_t get_index_in_buffer (size_t x, size_t y, size_t_vec2d shape);
size_t get_buffer_len (size_t_vec2d buffer_size);

void error_exit (string head, string message);


# endif // UTILS