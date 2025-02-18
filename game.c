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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Game interface implementation
*/
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
  int i=0;

  if (!game || !game->object)
  {
    return ERROR;
  }

  if ((object_set_id(game->object, id))==ERROR)
  {
    return ERROR;
  }
  
  while(i<game->n_spaces && space_get_id(game->spaces[i]) != id){
    i++;
  }
  
  space_set_object(game->spaces[i], object_get_id(game->object));

  return OK;
}

Status game_create(Game *game) {


  if (game_createspace(game)==ERROR)
  {
    return ERROR;
  }
 
  game->object=object_create(1);
  game->player=player_create(2);
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  /* Error Control */
  if (!game){
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  player_destroy(game->player);
  object_destroy(game->object);
  command_destroy(game->last_cmd);

  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
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