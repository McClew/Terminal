#ifndef DIALOGUE_H
#define DIALOGUE_H

#ifdef _WIN32
    #include <pdcurses.h>
#else
    #include <ncurses.h>
#endif

// The Dialogue "Object"
typedef struct {
    WINDOW *win;
    int width;
    int height;
    int is_active;
    int block_input;         // Flag to disable user input
    char **portrait_frames;  // Array of ASCII art strings
    int frame_count;
    int current_frame;
    char *current_text;      // The text currently being typed out
    int text_index;          // How many characters have been printed so far
} DialogueBox;

// Function signatures
DialogueBox* create_dialogue_box(int height, int width, int start_y, int start_x, int block_input);
void draw_dialogue_frame(DialogueBox *db);
void destroy_dialogue_box(DialogueBox *db);

#endif