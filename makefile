# Define compiler and basic flags
CC = clang
CFLAGS = -Wall -Wextra -Iinclude

# OS detection for cross-platform builds
ifeq ($(OS),Windows_NT)
    TARGET = terminal.exe
    CFLAGS += -IC:/msys64/ucrt64/include -DNCURSES_MOUSE_VERSION
    LIBS = -LC:/msys64/ucrt64/lib -lpdcurses
    CLEAN_CMD = del /Q $(TARGET)
else
    TARGET = terminal
    LIBS = -lncurses
    CLEAN_CMD = rm -f $(TARGET)
endif

# Find all source files in specified directories
SRCS = $(wildcard src/*.c src/controllers/*.c src/commands/*.c src/views/*.c)

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Cleanup rule
clean:
	$(CLEAN_CMD)