#ifndef UI_H
#define UI_H

// Function pointer for the action triggered on click
typedef void (*ButtonAction)(void);

typedef struct {
    int y;
    int x;
    int width;
    int height;
    const char *label;
    ButtonAction on_click;
} Button;

Button create_button(int y, int x, int width, int height, const char *label, ButtonAction action);
void draw_button(Button *btn);
int handle_button_click(Button *btn, int mouse_y, int mouse_x);

#endif