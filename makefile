EXE = hormiguero
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
LDLIBS = -L. -lscreen
OBJ = command.o set.o space.o player.o object.o character.o game.o game_actions.o graphic_engine.o game_reader.o game_loop.o
SET_TEST = set_test.o set.o
CHARACTER_TEST = character_test.o character.o
SPACE_TEST = space_test.o space.o set.o character.o


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)

set_test: $(SET_TEST)
	$(CC) $(CFLAGS) -o set_test $(SET_TEST)

character_test: $(CHARACTER_TEST)
	$(CC) $(CFLAGS) -o character_test $(CHARACTER_TEST)

space_test: $(SPACE_TEST)
	$(CC) $(CFLAGS) -o space_test $(SPACE_TEST)

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

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c character.c

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

set_test.o: set_test.c set_test.h set.h test.h
	$(CC) $(CFLAGS) -c set_test.c

character_test.o: character_test.c character_test.h character.h test.h
	$(CC) $(CFLAGS) -c character_test.c

space_test.o: space_test.c space_test.h space.h set.h character.h test.h
	$(CC) $(CFLAGS) -c space_test.c

run_set_test: 
	./set_test

run_character_test:
	./character_test

run_space_test:
	./space_test

clean :
	rm -rf $(OBJ) $(SET_TEST) $(CHARACTER_TEST) $(SPACE_TEST) $(EXE) 

run: 
	@echo "Running hormiguero"
	./hormiguero anthill.dat

runv:
	@echo "Running hormiguero with valgrind"
	valgrind --leak-check=full --track-origins=yes ./hormiguero anthill.dat
