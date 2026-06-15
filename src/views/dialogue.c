#include "dialogue.h"
#include <stdlib.h>

DialogueBox* create_dialogue_box(int height, int width, int start_y, int start_x, int block_input) {
    // Allocate memory for the object
    DialogueBox *db = malloc(sizeof(DialogueBox));
    
    db->height = height;
    db->width = width;
    db->block_input = block_input;
    db->is_active = 1;
    
    // Create the ncurses window
    db->win = newwin(height, width, start_y, start_x);
    
    // Draw a default box border
    box(db->win, 0, 0); 
    
    // Push window to the top layer and render it
    touchwin(db->win); 
    wrefresh(db->win);
    
    return db;
}

void destroy_dialogue_box(DialogueBox *db) {
    delwin(db->win);
    free(db);
}