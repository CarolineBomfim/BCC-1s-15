CC = gcc
CFLAGS = -std=c99 -W -Wall -pedantic 
EXEC = TrackTest
SRC = track_test.c ../src/camera.c ../src/track.c ../src/configure.c ../src/logger.c
FLAGS = -lallegro -lallegro_main -lallegro_color -lallegro_image -lallegro_font -lallegro_ttf \
		-lallegro_primitives -lallegro_audio -lallegro_acodec -lopencv_core -lopencv_highgui -lm

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ)
