EXE = hormiguero
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
LDLIBS = -L. -lscreen
OBJ = command.o set.o space.o player.o object.o game.o game_actions.o graphic_engine.o game_reader.o game_loop.o


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)


command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

space.o: space.c space.h set.h types.h 
	$(CC) $(CFLAGS) -c space.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

game.o: game.c game.h command.h types.h space.h game_reader.h player.h object.h
	$(CC) $(CFLAGS) -c game.c

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h player.h object.h
	$(CC) $(CFLAGS) -c game_actions.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h libscreen.h
	$(CC) $(CFLAGS) -c graphic_engine.c

game_reader.o: game_reader.c game_reader.h command.h types.h space.h player.h object.h game.h
	$(CC) $(CFLAGS) -c game_reader.c

game_loop.o: game_loop.c command.h types.h game.h space.h game_actions.h graphic_engine.h game_reader.h
	$(CC) $(CFLAGS) -c game_loop.c

clean :
	rm -rf $(OBJ)

run: 
	@echo "Running hormiguero"
	./hormiguero anthill.dat

runv:
	@echo "Running hormiguero with valgrind"
	valgrind --leak-check=full --track-origins=yes ./hormiguero anthill.dat
