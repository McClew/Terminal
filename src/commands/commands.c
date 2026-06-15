#include "commands.h"
#include "dialogue.h"
#include <string.h>

#ifdef _WIN32
    #include <pdcurses.h>
#else
    #include <ncurses.h>
#endif

void prog_test() {
    // Trigger the new dialogue box code
    DialogueBox *db = create_dialogue_box(10, 50, 2, 2, 1);
    
    // For now, we will just print a test string inside it
    mvwprintw(db->win, 1, 1, "Test programme executed.");
    wrefresh(db->win);
}

void exit_cmd(int *running) {
	*running = 0;
}

// Command registry
Command command_table[] = {
    {"test", prog_test},
    {"exit", exit_cmd},
    {NULL, NULL}
};

void execute_command(char *input, int *running) {
    printw("\n");

    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strcmp(input, command_table[i].name) == 0) {
            command_table[i].execute(running);
            return;
        }
    }
    
    if (strlen(input) > 0) {
        printw("Command not found: %s", input);
    }
}