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
#include <time.h>

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
void game_actions_take(Game *game, char *object);

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
 * @brief It attacks an unfriendly character
 * @author Duna Puente
 *
 * @param game A pointer to the game
 * @param character The name of the character
 */
void game_actions_attack(Game *game);

/**
 * @brief It lets the player talk to other characters
 * @author Duna Puente
 *
 * @param game Pointer to the game
 * @param character The name of a character
 */
void game_actions_chat(Game *game);

/**
   Game actions implementation
*/

/**/
Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;
  char *object = "grain"; /*Arreglar*/

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
    game_actions_take(game, object);
    break;

  case DROP:
    game_actions_drop(game);
    break;

  case LEFT:
    game_actions_left(game);
    break;

  case RIGHT:
    game_actions_right(game);
    break;

  case ATTACK:
    game_actions_attack(game);
    break;

  case CHAT:
    game_actions_chat(game);
    break;

  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) { game_set_last_command_status(game, "ERROR"); }

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game)
{
  Id current_id = NO_ID, object_id = NO_ID;
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
    object_id = game_player_get_object(game);
    if (object_id != NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    game_set_last_command_status(game, "OK");
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID, object_id = NO_ID;
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
    object_id = game_player_get_object(game);
    if (object_id != NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    game_set_last_command_status(game, "OK");
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }
}

void game_actions_take(Game *game, char *object)
{
  Space *space = game_get_space(game, game_get_player_location(game));
  Id object_id = game_get_object_id_from_name(game, object);

  if (game == NULL)
  {
    return;
  }

  if (game_get_player_location(game) == game_get_object_location(game, object_id))
  {
    game_player_set_object(game, object_id);
    space_set_object(space, NO_ID);
    game_set_object_location(game, NO_ID, NO_ID);
    game_set_last_command_status(game, "OK");
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }
}

void game_actions_drop(Game *game)
{
  Id player_location = game_get_player_location(game);
  Id object_id = NO_ID;

  if (game == NULL)
  {
    return;
  }

  object_id = game_player_get_object(game);
  if (object_id != NO_ID)
  {
    game_set_object_location(game, object_id, player_location);
    game_player_set_object(game, NO_ID);
    game_set_last_command_status(game, "OK");
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }
}

void game_actions_left(Game *game)
{

  Id current_id = NO_ID, object_id = NO_ID;
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
    object_id = game_player_get_object(game);
    if (object_id != NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    game_set_last_command_status(game, "OK");
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }

  return;
}

void game_actions_right(Game *game)
{
  Id current_id = NO_ID, object_id = NO_ID;
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
    object_id = game_player_get_object(game);
    if (object_id != NO_ID)
    {
      game_set_object_location(game, object_id, NO_ID);
    }
    game_set_last_command_status(game, "OK");
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }

  return;
}

void game_actions_attack(Game *game)
{
  int n;
  char *character = NULL;
  time_t t;

  if (!game)
  {
    return;
  }

  character = game_space_get_character_name(game);

  if ((game_get_character_location_from_name(game, character) == game_get_player_location(game)) &&
      (game_get_charatcter_friendly(game, character) == FALSE))
  {
    if ((game_get_character_health(game, character) != 0) && (game_get_player_health(game) != 0))
    {
      srand((unsigned)time(&t));
      n = 0 + rand() % (9 - 0 + 1);
      if (0 <= n && n <= 4)
      {
        game_player_set_health(game, (game_get_player_health(game) - 1));
        game_set_last_command_status(game, "OK");
      }
      else if (5 <= n && n <= 9)
      {
        game_character_set_health(game, character, (game_get_character_health(game, character) - 1));
        game_set_last_command_status(game, "OK");
      }
      else
      {
        game_set_last_command_status(game, "ERROR");
      }
    }
    else
    {
      game_set_last_command_status(game, "ERROR");
    }
  }
  else
  {
    game_set_last_command_status(game, "ERROR");
  }

  free(character);
  return;
}

void game_actions_chat(Game *game)
{
  char *character = NULL, *message=NULL;
  char default_message[] = "This character isn't friendly or there is no character";

  if (!game)
  {
    return;
  }

  character = game_space_get_character_name(game);

  /*if (!character)
  {
    game_set_last_message(game, default_message);
    game_set_last_command_status(game, "ERROR");
  }*/
  

  if ((game_get_character_location_from_name(game, character) == game_get_player_location(game)) &&
      (game_get_charatcter_friendly(game, character) == TRUE))
  {
    message=game_get_character_message(game, character);
    game_set_last_message(game, message);
    game_set_last_command_status(game, "OK");
    free(message);
  }
  else
  {
    game_set_last_message(game, default_message);
    game_set_last_command_status(game, "ERROR");
  }

  if (character)
  {
    free(character);
  }
  
}