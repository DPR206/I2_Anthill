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
  Object *objects[MAX_OBJECTS];
  Space *spaces[MAX_SPACES];
  Character *characters[MAX_CHARACTERS];
  int n_spaces;
  int n_objects;
  int n_characters;
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
   Implementation of private functions
*/

Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= game_get_numspaces(game))
  {
    return NO_ID;
  }

  return space_get_id(game_get_space(game, position));
}

/**
   Game interface implementation
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

Status game_add_object(Game *game, Object *object)
{
  if (object == NULL)
  {
    return ERROR;
  }

  game->objects[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Status game_add_character(Game *game, Character *character)
{


  if (character == NULL)
  {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

Game *game_create()
{
  Game *gm = NULL;
  int i;

  gm = (Game *)calloc(1, sizeof(Game));

  if (!gm)
  {
    return NULL;
  }

  if (game_createspace(gm) == ERROR)
  {
    return NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    gm->objects[i] = NULL;
  }
  gm->n_objects = 0;
  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    gm->characters[i] = NULL;
  }
  gm->n_characters = 0;
  gm->player = player_create(NO_ID);
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

Status game_create_from_file(Game *game, char *filename)
{
  if (game == NULL)
  {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_reader_load_objects(game, filename) == ERROR)
  {
    return ERROR;
  }
  if(game_reader_load_characters(game, filename)==ERROR){
    return ERROR;
  }

  /* The player is located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));

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

Id game_get_object_location(Game *game, Id object)
{
  int i = 0;

  if (object == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (set_contains(space_get_objects(game->spaces[i]), object) == TRUE)
    {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Id game_get_object_location_from_name(Game *game, char *object)
{
  int i;
  Id object_id = NO_ID;

  if (object == NULL)
  {
    return NO_ID;
  }

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (object_get_name(game->objects[i]) == object)
    {
      object_id = object_get_id(game->objects[i]);
    }
  }
  /*if (object_id == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (set_contains(space_get_objects(game->spaces[i]), object_id) == TRUE)
    {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;*/
}

Status game_set_object_location(Game *game, Id object, Id location)
{
  int i = 0;

  if (!game)
  {
    return ERROR;
  }

  while (i < game->n_spaces && space_get_id(game->spaces[i]) != location)
  {
    i++;
  }

  space_set_object(game->spaces[i], object);

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
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    object_destroy(game->objects[i]);
  }
  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    character_destroy(game->characters[i]);
  }
  command_destroy(game->last_cmd);

  free(game);
  return OK;
}

Status game_set_last_command(Game *game, Command *command)
{
  (game->last_cmd) = command;

  return OK;
}

Command *game_get_last_command(Game *game)
{
  if (!game)
  {
    return NULL;
  }

  return game->last_cmd;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished)
{
  (game->finished) = finished;

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

  printf("=> Grain location: %d\n", (int)game_get_object_location_from_name(game, "Grain"));
  printf("=> Crumb location: %d\n", (int)game_get_object_location_from_name(game, "Crumb"));
  printf("=> Leaf location: %d\n", (int)game_get_object_location_from_name(game, "Leaf"));
  printf("=> Seed location: %d\n", (int)game_get_object_location_from_name(game, "Seed"));
  printf("=> Player location: %d\n", (int)player_get_id(game->player));
}

Id game_player_get_object(Game *game)
{
  return player_get_object(game->player);
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
