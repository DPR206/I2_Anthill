/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This struct stores all the information of a game
 *
 */
struct _Game
{
  Command *last_cmd;
  Bool finished;
  Player *player;
  Object *object;
  Space *spaces[MAX_SPACES];
  int n_spaces;
};

/**
 * @brief It gets the space ID at a specific position
 * @author Profesores PPROG
 * 
 * @param game Pointer to the game
 * @param position Position to get its space ID 
 * @return The ID at the specific position, or NO_ID if the position is not valid
 */
Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/
Game *game_create()
{

  Game *gm = NULL;

  gm = (Game *)calloc(1, sizeof(Game));

  if (!gm)
  {
    return NULL;
  }

  if (game_createspace(gm) == ERROR)
  {
    return NULL;
  }

  gm->object = object_create(1);
  gm->player = player_create(2);
  gm->last_cmd = command_create();
  gm->finished = FALSE;

  return gm;
}

Status game_createspace(Game *game)
{
  int i;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;

  return OK;
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) { return player_get_location(game->player); }

Status game_set_player_location(Game *game, Id id)
{
  if (id == NO_ID)
  {
    return ERROR;
  }

  if (!(player_set_location(game->player, id)))
  {
    return ERROR;
  }

  return OK;
}

Id game_get_object_location(Game *game)
{
  return object_get_id(game->object);
}

Status game_set_object_location(Game *game, Id id)
{
  int i = 0;

  if (!game || !game->object)
  {
    return ERROR;
  }

  if ((object_set_id(game->object, id)) == ERROR)
  {
    return ERROR;
  }

  while (i < game->n_spaces && space_get_id(game->spaces[i]) != id)
  {
    i++;
  }

  space_set_object(game->spaces[i], object_get_id(game->object));

  return OK;
}

Status game_destroy(Game *game)
{
  int i = 0;

  /* Error Control */
  if (!game)
  {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    space_destroy(game->spaces[i]);
  }

  player_destroy(game->player);
  object_destroy(game->object);
  command_destroy(game->last_cmd);

  return OK;
}

Command *game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command)
{
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished)
{
  game->finished = finished;

  return OK;
}

void game_print(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)object_get_id(game->object));
  printf("=> Player location: %d\n", (int)player_get_id(game->player));
}

Status game_create_from_file(Game *game, char *filename)
{

  game = game_create();

  if (game == NULL)
  {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR)
  {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  free(game);

  return OK;
}

Id game_player_get_object(Game *game)
{
  return player_get_object(game->player);
}

Id game_object_get_id(Game *game)
{
  return object_get_id(game->object);
}

Status game_player_set_object(Game *game, Id id)
{
  if (!game)
  {
    return ERROR;
  }

  player_set_object(game->player, id);
  return OK;
}

int game_get_numspaces(Game *game) { return game->n_spaces; }

Status game_add_numspaces(Game *game)
{
  game->n_spaces++;
  return OK;
}

Status game_add_newspace(Game *game, Space *space)
{
  if (!space)
  {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;

  return OK;
}

/**
   Implementation of private functions
*/

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game_get_numspaces(game) >= MAX_SPACES))
  {
    return ERROR;
  }

  game_add_newspace(game, space);
  game_add_numspaces(game);

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= game_get_numspaces(game))
  {
    return NO_ID;
  }

  return space_get_id(game_get_space(game, position));
  /*return space_get_id(game->spaces[position]);*/
}

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game_get_numspaces(game) >= MAX_SPACES))
  {
    return ERROR;
  }

  game_add_newspace(game, space);
  game_add_numspaces(game);

  return OK;
}
