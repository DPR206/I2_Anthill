/**
 * @brief It implements the player module
 * 
 * @file player.c
 * @author Duna Puente
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Player
 * 
 * This struct stores all the information of player
 */
struct _Player
{
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Id object;
  int health;
};

Player *player_create(Id id)
{
  Player *newplayer = NULL;

  /* Error control */
  if (id == NO_ID)
  {
    return NULL;
  }

  newplayer = (Player *)calloc(1, sizeof(Player));

  /* Error control */
  if (!newplayer)
  {
    return NULL;
  }

  /* Initializing new player */
  newplayer->id = id;
  newplayer->name[0] = '\0';
  newplayer->object=NO_ID;

  return newplayer;
}

Status player_destroy(Player *player)
{
  /* Error control */
  if (!player)
  {
    return ERROR;
  }

  free(player);

  return OK;
}

Id player_get_id(Player *player)
{
  /* Error control */
  if (!player)
  {
    return NO_ID;
  }

  return player->id;
}

Status player_set_name(Player *player, char *name)
{
  /* Error control */
  if (!player || !name)
  {
    return ERROR;
  }

  if (!strcpy(player->name, name))
  {
    return ERROR;
  }

  return OK;
}

const char *player_get_name(Player *player)
{
  /* Error control */
  if (!player)
  {
    return NULL;
  }

  return player->name;
}

Status player_set_object(Player *player, Id object)
{
  /* Error control */
  if (!player)
  {
    return ERROR;
  }

  player->object=object;

  return OK;
  
}

Id player_get_object(Player *player)
{
  /* Error control */
  if (!player)
  {
    return NO_ID;
  }

  return player->object;
}

Status player_set_location(Player *player, Id id)
{
  /* Error control */
  if (!player || id == NO_ID)
  {
    return ERROR;
  }

  player->location = id;

  return OK;
}

Id player_get_location (Player *player)
{
  /* Error control */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->location;
}

Status player_print(Player *player)
{

  /* Error control */
  if (!player)
  {
    return ERROR;
  }

  /* Print the id, the name and the object of the player */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s; Object: %ld)\n", player->id, player->name, player->object);

  return OK;
}

Status player_set_health(Player *player, int health)
{
  /* Error control */
  if (!player)
  {
    return ERROR;
  }

  player->health=health;

  return OK;
  
}

int player_get_health(Player *player) { return player->health; }
