#include "ui.h"
#include <string.h>

#ifdef _WIN32
    #include <pdcurses.h>
#else
    #include <ncurses.h>
#endif

Button create_button(int y, int x, int width, int height, const char *label, ButtonAction action) {
    Button btn = {y, x, width, height, label, action};
    return btn;
}

void draw_button(Button *btn) {
    attron(A_REVERSE); 
    
    // Fill the button area
    for (int i = 0; i < btn->height; i++) {
        move(btn->y + i, btn->x);
        for (int j = 0; j < btn->width; j++) {
            printw(" "); 
        }
    }
    
    // Centre the label text
    int text_x = btn->x + (btn->width - strlen(btn->label)) / 2;
    int text_y = btn->y + (btn->height / 2);
    mvprintw(text_y, text_x, "%s", btn->label);
    
    attroff(A_REVERSE);
}

int handle_button_click(Button *btn, int mouse_y, int mouse_x) {
    // Check if coordinates overlap the button's area
    if (mouse_y >= btn->y && mouse_y < btn->y + btn->height &&
        mouse_x >= btn->x && mouse_x < btn->x + btn->width) {
        
        if (btn->on_click) {
            btn->on_click(); // Execute the assigned function
        }
        return 1; 
    }
    return 0;
}