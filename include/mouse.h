#ifndef MOUSE_H
#define MOUSE_H

#ifdef _WIN32
#include <pdcurses.h>
#else
#include <ncurses.h>
#endif

void process_mouse(MEVENT *event);

#endif