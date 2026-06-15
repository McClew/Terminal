#include "mouse.h"
#include "input.h"
#include "ui.h"
#include <stdio.h>

void process_mouse(MEVENT *event) {
	// If it's a left click, handle in-game mouse clicks here
	if (event->bstate & BUTTON1_CLICKED) {
		// handle_in_game_click(event->y, event->x);
	}
}