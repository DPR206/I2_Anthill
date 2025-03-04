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
 * @brief It moves the player to the space to the left
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 */
void game_actions_left(Game *game);

/**
 * @brief It moves the player to the space to the right
 * @author Duna Puente
 * 
 * @param game A pointer to the game
 */
void game_actions_right(Game *game);

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
  Id current_id = NO_ID, object_id=NO_ID;
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
    object_id=game_player_get_object(game);
    if (object_id!=NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    
  }

  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID, object_id=NO_ID;
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
    object_id=game_player_get_object(game);
    if (object_id!=NO_ID) 
    {
      game_set_object_location(game, object_id, NO_ID);
    }
  }
}

void game_actions_take(Game *game) /*Cambiar todo ahora que hay varios objetos*/
{ 
  Space *space = game_get_space(game, game_get_player_location(game));
  Id object_id = NO_ID;/*game_get_object_id(game);*/ 

  if (game == NULL)
  {
    return;
  }

  if (game_get_player_location(game) == game_get_object_location(game, object_id)) 
  {
    game_player_set_object(game, object_id);
    space_set_object(space, NO_ID);
    game_set_object_location(game, NO_ID, NO_ID);  
  }
}

void game_actions_drop(Game *game) 
{
  Id player_location = game_get_player_location(game);
  Id object_id=NO_ID;

  if (game == NULL)
  {
    return;
  }

  object_id=game_player_get_object(game);
  if (object_id != NO_ID) 
  {
    game_set_object_location(game, object_id, player_location);
    game_player_set_object(game, NO_ID);
  }
}

void game_actions_left(Game *game)
{

  Id current_id = NO_ID, object_id=NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
    object_id=game_player_get_object(game);
    if (object_id!=NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    
  }

  return;
  
}

void game_actions_right(Game *game)
{
  Id current_id = NO_ID, object_id=NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
    object_id=game_player_get_object(game);
    if (object_id!=NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    
  }

  return;
}
