CC = g++
SOURCES = main.cpp paddle.cpp ball.cpp
LFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
EXE_NAME = pong
$(EXE_NAME): $(SOURCES)
	$(CC) $(SOURCES) $(LFLAGS) -o $(EXE_NAME)
