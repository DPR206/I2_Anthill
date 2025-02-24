/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"
#include "player.h"
#include "object.h"

/**
 * @brief It updates the game state, calls the corresponding function based on the given command
 * @author Claudia Saiz
 *
 * @param game Pointer to the game
 * @param cmd Pointer to the command that determines the action to perform
 * @return Status, OK if successful
 */
Status game_actions_update(Game *game, Command *cmd);


#endif
