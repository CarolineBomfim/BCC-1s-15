CC = gcc
CFLAGS = -std=c99 -W -Wall -pedantic
EXEC = AirDrums
SRC = $(wildcard src/*.c)
FLAGS = -lallegro -lallegro_main -lallegro_color -lallegro_image -lallegro_font -lallegro_ttf \
				-lallegro_primitives -lallegro_audio -lallegro_acodec -lopencv_core -lopencv_highgui -lm

all: $(EXEC)

OBJ: $(SRC)
	$(CC) $(CFLAGS) $^ -c

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ)