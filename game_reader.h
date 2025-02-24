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
 * @brief It loads game spaces from a file
 * @author Duna Puente
 *
 * @param game Pointer to the game
 * @param filename Name of the file containing space data
 * @return Status of the operation: ERROR if failed, OK if successful.
 */
Status game_reader_load_spaces(Game *game, char *filename);

#endif
