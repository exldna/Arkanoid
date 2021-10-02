# include "console.h"


extern OutputBufferSize WINDOW_SIZE;

extern size_t_vec2d CONSOLE_BUFFER_SIZE;
extern size_t CONSOLE_BUFFER_LEN;

extern OutputBuffer console_output_buffer;
extern ConsoleDescriptor console_descriptor;


HANDLE get_std_handle (DWORD handle_type)
{
	HANDLE std_handle = GetStdHandle (handle_type);
	if (std_handle == INVALID_HANDLE_VALUE)
	{
		error_exit ("Console", "Invalid std-handle value");
	}

	return std_handle;
}

void set_buffer_size (HANDLE std_buffer_handle, COORD size)
{
	if (!SetConsoleScreenBufferSize (std_buffer_handle, size))
	{
		printf ("error code: %d\n", GetLastError ());
		error_exit ("Console", "Can't set screen buffer size");
	}
}

void set_window_size (HANDLE std_buffer_handle, SMALL_RECT* size)
{
	if (!SetConsoleWindowInfo (std_buffer_handle, TRUE, size))
	{
		error_exit ("Console", "Can't set window info");
	}
}

void set_console_cursor_info (HANDLE std_buffer_handle, CONSOLE_CURSOR_INFO* info)
{
	if (!SetConsoleCursorInfo (std_buffer_handle, info))
	{
		error_exit ("Console", "Can't set console cursor info");
	}
}

void set_console_cursor_position (HANDLE std_buffer_handle, COORD position)
{
	SetConsoleCursorPosition (std_buffer_handle, position);
}

CONSOLE_SCREEN_BUFFER_INFO get_csbi (HANDLE std_buffer_handle, bool is_show)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo (std_buffer_handle, &csbi);

	if (is_show == true)
	{
		printf ("----- size\nwidth: %d\nheight: %d\n",
			csbi.dwSize.X,
			csbi.dwSize.Y
		);
		printf ("----- maximum window size\nwidth: %d\nheight: %d\n",
			csbi.dwMaximumWindowSize.X,
			csbi.dwMaximumWindowSize.Y
		);
		printf ("----- window\ntop: %d\nbottom: %d\nleft: %d\nright: %d\n",
			csbi.srWindow.Top,
			csbi.srWindow.Bottom,
			csbi.srWindow.Left,
			csbi.srWindow.Right
		);
	}

	return csbi;
}

void init_console ()
{
	// get console output buffer handle
	HANDLE std_output_handle = get_std_handle (STD_OUTPUT_HANDLE);

	// set window size
	SMALL_RECT console_window_size = {
		.Top = 0,
		.Left = 0,
		.Bottom = WINDOW_SIZE.y,
		.Right = WINDOW_SIZE.x
	};

	set_window_size (std_output_handle, &console_window_size);

	/* get min buffer size *
	* ==================== *
	CONSOLE_SCREEN_BUFFER_INFO csbi = get_csbi (std_output_handle, false);

	uint window_width = csbi.srWindow.Right - csbi.srWindow.Left;
	uint window_height = csbi.srWindow.Bottom - csbi.srWindow.Top;

	uint cxmin = GetSystemMetrics(SM_CXMIN);
	uint cymin = GetSystemMetrics(SM_CYMIN);

	uint min_buffer_size_x = max(window_width, cxmin);
	uint min_buffer_size_y = max(window_height, cymin);
	* ==================== */

	// set buffer size
	COORD output_buffer_size;
	output_buffer_size.X = WINDOW_SIZE.x + 1;
	output_buffer_size.Y = WINDOW_SIZE.y + 1;

	set_buffer_size (std_output_handle, output_buffer_size);

	// get_csbi (std_output_handle, true);

	// set cursor unvisible
	CONSOLE_CURSOR_INFO console_cursor_info = {
		.dwSize = 1,
		.bVisible = false
	};

	set_console_cursor_info (std_output_handle, &console_cursor_info);
	
	// set cursor default position
	console_descriptor.cursor_zero_pos.X = 0;
	console_descriptor.cursor_zero_pos.Y = 0;
	
	// set console discription
	console_descriptor.std_output_handle = std_output_handle;
}


void init_console_output_buffer ()
{
	// allocate memory from console_output_buffer
	console_output_buffer = malloc(CONSOLE_BUFFER_LEN);

	// fill console_output_buffer
	size_t i;

	for (size_t y = 0; y < CONSOLE_BUFFER_SIZE.y; ++y)
	{
		for (size_t x = 0; x < CONSOLE_BUFFER_SIZE.x - 1; ++x)
		{
			i = get_index_in_buffer (x, y, CONSOLE_BUFFER_SIZE);
			console_output_buffer[i] = ' ';
		}
		// add end-line char
		console_output_buffer[get_index_in_buffer(CONSOLE_BUFFER_SIZE.x - 1, y, CONSOLE_BUFFER_SIZE)] = '\n';
	}
}


void clear_console ()
{
	set_console_cursor_position (
		console_descriptor.std_output_handle, 
		console_descriptor.cursor_zero_pos
	);
}


void show_output_buffer ()
{
	clear_console (console_descriptor);

	uint number_of_chars_written = 0;

	WriteConsole (
		console_descriptor.std_output_handle, 
		console_output_buffer,
		CONSOLE_BUFFER_LEN,
		&number_of_chars_written, NULL
	);

	if (number_of_chars_written < CONSOLE_BUFFER_LEN)
	{
		error_exit (
			"WriteConsole",
			"Number of written characters is less of console output buffer size"
		);
	}
}