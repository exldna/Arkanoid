# include "utils.h"

# include <stdio.h>
# include <stdlib.h>


size_t get_index_in_buffer (size_t x, size_t y, size_t_vec2d shape)
{
# ifdef _DEBUG
	size_t ans = y * shape.x + x;

	if (ans >= shape.x * shape.y)
	{
		error_exit ("GetIndexInBuffer", "Out of range buffer indeces");
	}

	return ans;
# else
	return y * shape.x + x;
# endif
}


size_t get_buffer_len (size_t_vec2d buffer_size)
{
	return buffer_size.x * buffer_size.y;
}


void error_exit (string head, string message)
{
# ifdef _DEBUG
	fprintf (stderr, "ERROR :: %s :: %s\n", head, message);
	system ("pause");
# endif
	exit (-1);
}