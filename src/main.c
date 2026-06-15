#include "input.h"
#include "ui.h"
#include <stdlib.h>

// Check OS and include appropriate headers
// This provides cross-platform compatibility for the terminal
#ifdef _WIN32
#include <pdcurses.h>
#include <windows.h>
#else
#include <ncurses.h>
#endif

int app_state = 0; // 0 = main menu, 1 = terminal

void start_game(void) {
	app_state = 1;
}

void main_menu(void) {
	Button start_btn = create_button(10, 30, 20, 3, "START GAME", start_game);
	
	clear();
	draw_button(&start_btn);
	refresh();

	while (app_state == 0) {
		int character = getch();

		if (character == KEY_MOUSE) {
			MEVENT event;
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_CLICKED) {
					handle_button_click(&start_btn, event.y, event.x);
				}
			}
		} else if (character == 'q' || character == 'Q') {
			break; // Allow quitting the game from the menu
		}

		// Keep button drawn
		clear();
		draw_button(&start_btn);
		refresh();
	}
}

void terminal_loop(void) {
	int running = 1;
	char input[256];
	int length = 0;
	int cursor_position = 0;

	// Clear the screen from the main menu
	clear();

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

	// Enter the main menu first
	main_menu();

	// If the game started, enter the terminal loop
	if (app_state == 1) {
		terminal_loop();
	}

	// Restore the terminal to normal mode
	endwin();

	return 0;
}
