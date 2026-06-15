#ifndef COMMANDS_H
#define COMMANDS_H

// A function pointer type for all our terminal programmes
typedef void (*CommandFunction)(int *running);

// The Command Object
typedef struct {
    const char *name;
    CommandFunction execute;
} Command;

void execute_command(char *input, int *running);

#endif