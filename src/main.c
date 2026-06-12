#include "input.h"
#include <stdlib.h>

// Check OS and include appropriate headers
// This provides cross-platform compatibility for the terminal
#ifdef _WIN32
#include <pdcurses.h>
#include <windows.h>
#else
#include <ncurses.h>
#endif

void terminal_loop(void) {
	int running = 1;
	char input[256];
	int length = 0;
	int cursor_position = 0;

	printw("\n> ");
	refresh();

	while (running) {
		int character = getch(); // Capture keystroke

		process_keystroke(character, input, &length, &cursor_position, &running);

		refresh(); // Update the screen after every keystroke
	}
}

int main(void) {
	// Initialise the terminal
	initscr();            			// Take control of the terminal
	cbreak();             			// Disable line buffering (pass keys instantly)
	noecho();            			// Hide typed characters
	keypad(stdscr, TRUE);			// Capture special keys (arrows, function keys)
	mousemask(ALL_MOUSE_EVENTS, NULL);	// Capure mouse events

	// Config terminal window
	#ifdef _WIN32
		PDC_set_title("Terminal Loop");
		HWND hwnd = FindWindowA(NULL, "Terminal Loop");
		if (hwnd) {
			SetMenu(hwnd, NULL);

			// Force Windows to recalculate the title bar hitboxes
			SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		}
	#endif

	// Output and render
	terminal_loop();

	// Restore the terminal to normal mode
	endwin();

	return 0;
}
