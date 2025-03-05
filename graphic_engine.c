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

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 48
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 13
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_id=NO_ID;
  Id grain_loc=NO_ID, crumb_loc=NO_ID, leaf_loc=NO_ID, seed_loc=NO_ID;
  Id spider_loc=NO_ID, ant_loc=NO_ID;
  int spider_salud=0, ant_salud=0;
  Space *space_act = NULL;
  char *spider_gdesc, *ant_gdesc;
  char obj = '\0';
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

    if (game_get_object_location(game, obj_id) == id_back)  /*Apaño de obj_id, for para ver si algun onjeto del set structure objects contiene ese location*/
      obj = '*';
    else
      obj = ' ';

    if (id_back != NO_ID)
    {
      sprintf(str, "  |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game, obj_id) == id_act) /*Apaño de obj_id, for para ver si algun onjeto del set structure objects contiene ese location*/
      obj = '*';
    else
      obj = ' ';

    if (id_act != NO_ID)
    {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^     %2d|", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game, obj_id) == id_next) /*Apaño de obj_id, for para ver si algun onjeto del set structure objects contiene ese location*/
      obj = '*';
    else
      obj = ' ';

    if (id_next != NO_ID)
    {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  grain_loc = game_get_object_location_from_name(game, "Grain");
  crumb_loc = game_get_object_location_from_name(game, "Crumb");
  leaf_loc = game_get_object_location_from_name(game, "Leaf");
  seed_loc = game_get_object_location_from_name(game, "Seed");
  spider_gdesc=game_get_character_gdesc(game, "Spider");
  spider_loc=game_get_character_location(game, "Spider");
  spider_salud=game_get_character_salud(game, "Spider");
  ant_gdesc=game_get_character_gdesc(game, "Ant");
  ant_loc=game_get_character_location(game, "Ant");
  ant_salud=game_get_character_salud(game, "Ant");
  
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
  sprintf(str, "Characters:  ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s :%d (%d)", spider_gdesc, spider_loc, spider_salud);
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s :%d (%d)", ant_gdesc, ant_loc, ant_salud);
  screen_area_puts(ge->descript, str);
  /*Falta poner los characters y player (posicion y salud), y message*/
  

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
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
