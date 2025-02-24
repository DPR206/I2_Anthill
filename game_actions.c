/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief It handles the unknown command
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 */
void game_actions_unknown(Game *game);

/**
 * @brief It is used to exit the game
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 */
void game_actions_exit(Game *game);

/**
 * @brief It moves the player to the next space in the game, if available
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 */
void game_actions_next(Game *game);

/**
 * @brief It moves the player to the previous space in the game, if available
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 */
void game_actions_back(Game *game);

/**
 * @brief It lets the player take the object from a  space
 * @author Claudia Saiz
 *
 * @param game Pointer to the game
 */
void game_actions_take(Game *game);

/**
 * @brief It lets the player drop the object it carries in the space it is in
 * @author Claudia Saiz
 *
 * @param game Pointer to the game
 */
void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

/**/
Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd)
  {
  case UNKNOWN:
    game_actions_unknown(game);
    break;

  case EXIT:
    game_actions_exit(game);
    break;

  case NEXT:
    game_actions_next(game);
    break;

  case BACK:
    game_actions_back(game);
    break;

  case TAKE:
    game_actions_take(game);
    break;

  case DROP:
    game_actions_drop(game);
    break;

  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
    if (game_player_get_object(game)==game_object_get_id(game))
    {
      game_set_object_location(game, NO_ID);
    }
    
  }

  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
    if (game_player_get_object(game)==game_object_get_id(game)) 
    {
      game_set_object_location(game, NO_ID);
    }
  }
}

void game_actions_take(Game *game) 
{ 
  Space *space = game_get_space(game, game_get_player_location(game));
  Id object_id = game_object_get_id(game); 

  if (game == NULL)
  {
    return;
  }

  if (game_get_player_location(game) == game_get_object_location(game)) 
  {
    game_player_set_object(game, object_id);
    space_set_object(space, NO_ID);
    game_set_object_location(game, NO_ID);  
  }
}

void game_actions_drop(Game *game) 
{
  Id player_location = game_get_player_location(game);

  if (game == NULL)
  {
    return;
  }

  if (game_player_get_object(game) != NO_ID) 
  {
    game_set_object_location(game, player_location);
    game_player_set_object(game, NO_ID);
    /*space_set_object(space, object_id);*/
  }
}
