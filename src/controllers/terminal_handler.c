#include "terminal_handler.h"
#include "input.h"
#include <string.h>

// Check OS and include appropriate headers
// This provides cross-platform compatibility for the terminal
#ifdef _WIN32
#include <pdcurses.h>
#else
#include <ncurses.h>
#endif

void handle_backspace(char *input, int *length, int *cursor_position) {
	if (*cursor_position > 0 && *length > 0) {
		// Shift all characters after the cursor position back by 1
		for (int i = *cursor_position; i <= *length; i++) {
            input[i - 1] = input[i];
        }

		(*cursor_position)--;
        (*length)--;

        int y, x;
        getyx(stdscr, y, x);
        int start_x = x - 1;
        move(y, start_x);

		// Reprint the string from the new cursor position
        for (int i = *cursor_position; i < *length; i++) {
            addch(input[i]);
        }

        addch(' ');
        move(y, start_x);
	}
}

void handle_delete(char *input, int *length, int *cursor_position) {
	if (*cursor_position < *length) {
		// Shift all characters at the cursor position back by 1
		for (int i = *cursor_position; i < *length; i++) {
            input[i] = input[i + 1];
        }

        // Update state
        (*length)--;
		// Null-terminate the string
		input[*length] = '\0';

        // Visual redraw
        int y, x;
        getyx(stdscr, y, x);

        // Reprint the string from the cursor onwards
        for (int i = *cursor_position; i < *length; i++) {
            addch(input[i]);
        }

        // Clear to the end of the line
        clrtoeol();
        // Move cursor to the correct position
        move(y, x);
	}
}

void handle_enter(char *input, int *length, int *cursor_position, int *running) {
	input[*cursor_position] = '\0';

	if (strcmp(input, "exit") == 0) {
		*running = 0;
	} else {
		printw("\n%s is an unrecognised command\n> ", input);
	}

	*cursor_position = 0;
	*length = 0;
}

void handle_arrow_left(int *length, int *cursor_position) {
	if (*cursor_position > 0 && *length > 0) {
		(*cursor_position)--;

		int y, x;
		getyx(stdscr, y, x);
		move(y, x - 1);
	}
}

void handle_arrow_right(int *length, int *cursor_position) {
	if (*cursor_position < *length) {
		(*cursor_position)++;

		int y, x;
		getyx(stdscr, y, x);
		move(y, x + 1);
	}
}

void handle_character(char *input, int *length, int *cursor_position, char character) {
	if (*length < 255) {
		// Shift characters right to make room
		for (int i = *length; i > *cursor_position; i--) {
			input[i] = input[i - 1];
		}
		
		input[*cursor_position] = character;
		(*cursor_position)++;
		(*length)++;
		input[*length] = '\0';
		
		int y, x;
		getyx(stdscr, y, x);
		
		// Reprint the string from the inserted character onwards
		for (int i = *cursor_position - 1; i < *length; i++) {
			addch(input[i]);
		}
		
		// Move cursor to the correct position (after the typed character)
		move(y, x + 1);
	}
}