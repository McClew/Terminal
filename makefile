# Define compiler and basic flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# OS detection for cross-platform builds
ifeq ($(OS),Windows_NT)
    TARGET = terminal.exe
    LIBS = -lpdcurses
    CLEAN_CMD = del /Q $(TARGET)
else
    TARGET = terminal
    LIBS = -lncurses
    CLEAN_CMD = rm -f $(TARGET)
endif

# Find all source files in specified directories
SRCS = $(wildcard src/*.c src/controllers/*.c)

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Cleanup rule
clean:
	$(CLEAN_CMD)