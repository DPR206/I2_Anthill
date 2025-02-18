/**
 * @brief It define the game reader module interface
 * 
 * @file game_reader.h
 * @author Duna Puente
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER
#define GAME_READER

#include "command.h"
#include "types.h"
#include "game.h"

#define MAX_SPACES 100

/**
 * @brief creates a new game from a file, loads spaces from a specified file, and sets the initial player and object locations to the first space
 * @author Profesores PPROG
 *
 * @param game Pointer to the game to initialize
 * @param filename Name of the file with the space data
 * @return Status of the operation: ERROR if initialization fails, OK if successful
 */
Status game_create_from_file(Game *game, char *filename);

#endif