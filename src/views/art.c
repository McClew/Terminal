#include "art.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define custom COLOR_PAIR IDs for standard colors.
// Using values high enough to avoid conflicting with typical pair IDs, 
// though adjust these as necessary for your project.
#define ART_COLOR_PAIR_RED     101
#define ART_COLOR_PAIR_GREEN   102
#define ART_COLOR_PAIR_YELLOW  103
#define ART_COLOR_PAIR_BLUE    104
#define ART_COLOR_PAIR_MAGENTA 105
#define ART_COLOR_PAIR_CYAN    106
#define ART_COLOR_PAIR_WHITE   107

void init_art_colours(void) {
    // Note: start_color() should have been called in your application's setup
    init_pair(ART_COLOR_PAIR_RED,     COLOR_RED,     COLOR_BLACK);
    init_pair(ART_COLOR_PAIR_GREEN,   COLOR_GREEN,   COLOR_BLACK);
    init_pair(ART_COLOR_PAIR_YELLOW,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(ART_COLOR_PAIR_BLUE,    COLOR_BLUE,    COLOR_BLACK);
    init_pair(ART_COLOR_PAIR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(ART_COLOR_PAIR_CYAN,    COLOR_CYAN,    COLOR_BLACK);
    init_pair(ART_COLOR_PAIR_WHITE,   COLOR_WHITE,   COLOR_BLACK);
}

char* load_art_from_file(const char *filepath) {
    FILE *file = fopen(filepath, "rb"); // "rb" helps with exact size on Windows
    if (!file) {
        return NULL;
    }

    // Determine the length of the file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length < 0) {
        fclose(file);
        return NULL;
    }

    // Allocate memory plus space for a null-terminator
    char *buffer = (char *)malloc((size_t)length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t read_bytes = fread(buffer, 1, (size_t)length, file);
    buffer[read_bytes] = '\0';

    fclose(file);
    return buffer; // Caller is responsible for calling free(buffer)
}

// Helper to map color name strings to the mapped pair ID
static int get_color_pair_from_name(const char *name) {
    if (strcmp(name, "red") == 0) return ART_COLOR_PAIR_RED;
    if (strcmp(name, "green") == 0) return ART_COLOR_PAIR_GREEN;
    if (strcmp(name, "yellow") == 0) return ART_COLOR_PAIR_YELLOW;
    if (strcmp(name, "blue") == 0) return ART_COLOR_PAIR_BLUE;
    if (strcmp(name, "magenta") == 0) return ART_COLOR_PAIR_MAGENTA;
    if (strcmp(name, "cyan") == 0) return ART_COLOR_PAIR_CYAN;
    if (strcmp(name, "white") == 0) return ART_COLOR_PAIR_WHITE;
    return 0; // Invalid or default
}

void render_bbcode_art(WINDOW *win, int start_y, int start_x, const char *text) {
    if (!win || !text) return;

    int current_y = start_y;
    int current_x = start_x;
    int current_color_pair = 0; // 0 represents the default window color attribute

    const char *p = text;
    while (*p != '\0') {
        if (*p == '\r') {
            // Ignore carriage returns in CRLF sequences
            p++;
            continue;
        }
        
        if (*p == '\n') {
            current_y++;
            current_x = start_x;
            p++;
            continue;
        }

        // Parse possible BBCode tags
        if (*p == '[') {
            if (strncmp(p, "[color=", 7) == 0) {
                const char *tag_end = strchr(p + 7, ']');
                if (tag_end) {
                    size_t len = tag_end - (p + 7);
                    if (len > 0 && len < 20) {
                        char color_name[20];
                        strncpy(color_name, p + 7, len);
                        color_name[len] = '\0';
                        
                        int new_pair = get_color_pair_from_name(color_name);
                        if (new_pair > 0) {
                            if (current_color_pair > 0) {
                                wattroff(win, COLOR_PAIR(current_color_pair));
                            }
                            current_color_pair = new_pair;
                            wattron(win, COLOR_PAIR(current_color_pair));
                        }
                        
                        p = tag_end + 1; // Skip past ']'
                        continue;
                    }
                }
            } else if (strncmp(p, "[/color]", 8) == 0) {
                if (current_color_pair > 0) {
                    wattroff(win, COLOR_PAIR(current_color_pair));
                    current_color_pair = 0;
                }
                p += 8; // Skip the entire tag
                continue;
            }
        }

        // Draw normal character and advance
        mvwaddch(win, current_y, current_x, *p);
        current_x++;
        p++;
    }
    
    // Safety check: turn off the last color attribute if still active
    if (current_color_pair > 0) {
        wattroff(win, COLOR_PAIR(current_color_pair));
    }
}
