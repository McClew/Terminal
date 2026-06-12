#ifndef TERMINAL_HANDLER_H
#define TERMINAL_HANDLER_H
void handle_backspace(char *input, int *length, int *cursor_position);
void handle_delete(char *input, int *length, int *cursor_position);
void handle_enter(char *input, int *length, int *cursor_position, int *running);
void handle_arrow_left(int *length, int *cursor_position);
void handle_arrow_right(int *length, int *cursor_position);
void handle_character(char *input, int *length, int *cursor_position, char character);

#endif