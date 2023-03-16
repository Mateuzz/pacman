CC = gcc
CFLAGS = -O -Wall -W -Wextra -I/usr/include/SDL2

LD_FLAGS =  -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image

TARGET = Pacman

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
DEP = $(wildcard src/*.h)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LD_FLAGS)

-include %(DEP)

%(OBJ): $: $.c $(DEP)
	$(CC) $< -c -o $@ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf src/*.o $(TARGET)
