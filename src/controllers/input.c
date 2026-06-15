#include "mouse.h"
#include "input.h"
#include "terminal_handler.h"
#include <stdio.h>
#include <string.h>

// Check OS and include appropriate headers
// This provides cross-platform compatibility for the terminal
#ifdef _WIN32
#include <pdcurses.h>
#else
#include <ncurses.h>
#endif

void process_keystroke(int character, char *input, int *length, int *cursor_position, int *running) {
	if (character == 8 || character == 127){
		handle_backspace(input, length, cursor_position);
	} else if (character == 60490) {
		handle_delete(input, length, cursor_position);
	} else if (character == '\n' || character == '\r') {
		handle_enter(input, length, cursor_position, running);
	} else if (character == 60418) {
		//handle_arrow_down(input, length, cursor_position);
	} else if (character == 60419) {
		//handle_arrow_up(input, length, cursor_position);
	} else if (character == 60420) {
		handle_arrow_left(length, cursor_position);
	} else if (character == 60421) {
		handle_arrow_right(length, cursor_position);
	} else if (character >= 32 && character <= 126) {
		handle_character(input, length, cursor_position, character);
	} else if (character == KEY_MOUSE) {
		MEVENT event;
		if (getmouse(&event) == OK) {
			process_mouse(&event);
		}
	}
}