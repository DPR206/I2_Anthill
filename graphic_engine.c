/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 48
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 20
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3
#define G_SIZE 10

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
  {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
  {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID/*, id_right = NO_ID, id_left = NO_ID*/;
  Id grain_loc = NO_ID, crumb_loc = NO_ID, leaf_loc = NO_ID, seed_loc = NO_ID;
  Id obj_id = NO_ID;
  Id spider_loc = NO_ID, ant_loc = NO_ID, player_loc = NO_ID;
  Id player_object = NO_ID;
  int spider_health = 0, ant_health = 0, player_health = 0;
  Space *space_act = NULL, *space_back=NULL, *space_next=NULL;
  const char *spider_gdesc = NULL, *ant_gdesc = NULL;
  const char *command_result = "ERROR";
  char character_gdesc[G_SIZE] = " ";
  char *name=NULL;
  char obj[255]=" ";
  char str[255];
  int i;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  spider_gdesc = game_get_character_gdesc(game, "Spider");
  spider_loc = game_get_character_location_from_name(game, "Spider");
  spider_health = game_get_character_health(game, "Spider");
  ant_gdesc = game_get_character_gdesc(game, "Ant");
  ant_loc = game_get_character_location_from_name(game, "Ant");
  ant_health = game_get_character_health(game, "Ant");

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    space_back = game_get_space(game, id_back);
    space_next = game_get_space(game, id_next);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    /*id_right = space_get_east(space_act);
    id_left = space_get_west(space_act);*/

    for(i=0; i<MAX_SET; i++){
      obj_id = space_get_objects_id(space_act, i);

      name= game_get_object_name(game, obj_id);
      if(name!=NULL){
        strcat(obj, name);
      }
    }
    grain_loc = game_get_object_location_from_name(game, "Grain");
    crumb_loc = game_get_object_location_from_name(game, "Crumb");
    leaf_loc = game_get_object_location_from_name(game, "Leaf");
    seed_loc = game_get_object_location_from_name(game, "Seed");

    if (spider_loc == id_back)
    {
      strcpy(character_gdesc, spider_gdesc);
    }
    else if (ant_loc == id_back)
    {
      strcpy(character_gdesc, ant_gdesc);
    }
    else
    {
      strcpy(character_gdesc, " ");
    }
    if (id_back != NO_ID)
    {
      sprintf(str, "  |     %-6s %3d|", character_gdesc, (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %6s         |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    for(i=0; i<MAX_SET; i++){
      obj_id = space_get_objects_id(space_act, i);

      name= game_get_object_name(game, obj_id);
      if(name!=NULL){
        strcat(obj, name);
      }
    }
    if (spider_loc == id_act)
    {
      strcpy(character_gdesc, spider_gdesc);
    }
    else if (ant_loc == id_act)
    {
      strcpy(character_gdesc, ant_gdesc);
    }
    else
    {
      strcpy(character_gdesc, " ");
    }
    if (id_act != NO_ID)
    {
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^ %-6s %3d|", character_gdesc, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %6s         |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }

    for(i=0; i<MAX_SET; i++){
      obj_id = space_get_objects_id(space_act, i);

      name= game_get_object_name(game, obj_id);
      if(name!=NULL){
        strcat(obj, name);
      }
    }
    if (spider_loc == id_next)
    {
      strcpy(character_gdesc, spider_gdesc);
    }
    else if (ant_loc == id_next)
    {
      strcpy(character_gdesc, ant_gdesc);
    }
    else
    {
      strcpy(character_gdesc, " ");
    }
    if (id_next != NO_ID)
    {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %-6s %3d|", character_gdesc, (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  | %6s         |", obj);
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  player_loc = game_get_player_location(game);
  player_health = game_get_player_health(game);
  player_object = game_player_get_object(game);

  sprintf(str, "Objects:");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Grain:%d", (int)grain_loc);
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Crumb:%d", (int)crumb_loc);
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Leaf:%d", (int)leaf_loc);
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Seed:%d", (int)seed_loc);
  screen_area_puts(ge->descript, str);
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "Characters:  ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s : %d (%d)", spider_gdesc, (int)spider_loc, spider_health);
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s    : %d (%d)", ant_gdesc, (int)ant_loc, ant_health);
  screen_area_puts(ge->descript, str);
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "Player   : %d (%d)", (int)player_loc, player_health);
  screen_area_puts(ge->descript, str);
  if (player_object == NO_ID)
  {
    sprintf(str, "Player has no object");
    screen_area_puts(ge->descript, str);
  }
  else
  {
    sprintf(str, "Player has object: %s", game_get_object_name(game, player_object));
    screen_area_puts(ge->descript, str);
  }
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  /*Falta poner  message*/

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, left or l, right or r, exit or e, take or t, drop  or d, attack or a, chat or c");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  command_result = game_get_last_command_status(game);
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], command_result);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
