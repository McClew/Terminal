#ifndef ART_H
#define ART_H

#ifdef _WIN32
#include <pdcurses.h>
#else
#include <ncurses.h>
#endif

// Maps standard BBCode colour names to ncurses COLOR_PAIR IDs.
// Assumes start_color() has already been called.
void init_art_colours(void);

// Safely reads the entire text file into a dynamically allocated string buffer.
// Returns NULL on error. The returned string must be freed by the caller using free().
char* load_art_from_file(const char *filepath);

// Renders the loaded text to the specified window, parsing and hiding BBCode color tags.
void render_bbcode_art(WINDOW *win, int start_y, int start_x, const char *text);

#endif // ART_H
