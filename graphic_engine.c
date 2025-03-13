/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 2
 * @date 14-03-2025
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

#define WIDTH_MAP 60
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 29
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3
#define G_SIZE 6
#define OBJ_STR 15
#define SPACE_SIZE 20

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

/*Funciones privadas*/

/**
 * @brief It modifies a string to contain all of the objects of a space
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param space_id Id of the space
 * @param object String to contain the names of the objects
 */
void graphic_engine_objects_at_space(Game *game, Id space_id, char *object);

/**
 * @brief It modifies a string to contain the graphic descrition of a character in a space
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param space_id Id of the space
 * @param character_gdesc String to contain the gdesc of the character
 */
void graphic_engine_character_at_space(Game *game, Id space_id, char *character_gdesc);

/**
 * @brief It prints three consecutive spaces from the id of the space in the middle
 * @author Claudia Saiz
 * 
 * @param ge Pointer to the graphic engine
 * @param game Pointer to the game
 * @param space_id Id of the space in the middle
 * @return Status of the operation
 */
Status print_spaces(Graphic_engine *ge, Game *game, Id space_id);

/*Funciones publicas*/

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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  Id grain_loc = NO_ID, crumb_loc = NO_ID, leaf_loc = NO_ID, seed_loc = NO_ID;
  Id spider_loc = NO_ID, ant_loc = NO_ID, player_loc = NO_ID;
  Id player_object = NO_ID;
  int spider_health = 0, ant_health = 0, player_health = 0;
  Character *spider = NULL, *ant = NULL;
  Space *space_act = NULL;
  const char *spider_gdesc = NULL, *ant_gdesc = NULL;
  const char *command_result = "ERROR";
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  grain_loc = game_get_object_location_from_name(game, "Grain");
  crumb_loc = game_get_object_location_from_name(game, "Crumb");
  leaf_loc = game_get_object_location_from_name(game, "Leaf");
  seed_loc = game_get_object_location_from_name(game, "Seed");

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

    grain_loc = game_get_object_location_from_name(game, "Grain");
    crumb_loc = game_get_object_location_from_name(game, "Crumb");
    leaf_loc = game_get_object_location_from_name(game, "Leaf");
    seed_loc = game_get_object_location_from_name(game, "Seed");

    print_spaces(ge, game, id_back);

    if (id_back != NO_ID)
    {
      sprintf(str, "%28s^%28s", " ", " ");
      screen_area_puts(ge->map, str);
    }

    print_spaces(ge, game, id_act);

    if (id_next != NO_ID)
    {
      sprintf(str, "%28sv%28s", " ", " ");
      screen_area_puts(ge->map, str);
    }

    print_spaces(ge, game, id_next);
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  player_loc = game_get_player_location(game);
  player_health = game_get_player_health(game);
  player_object = game_player_get_object(game);

  spider = game_get_character_from_name(game, "Spider");
  spider_gdesc = game_get_character_gdesc(game, spider);
  spider_loc = game_get_character_location(game, spider);
  spider_health = game_get_character_health(game, spider);

  ant = game_get_character_from_name(game, "Ant");
  ant_gdesc = game_get_character_gdesc(game, ant);
  ant_loc = game_get_character_location(game, ant);
  ant_health = game_get_character_health(game, ant);

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
  sprintf(str, "Message: %s", game_get_last_message(game));
  screen_area_puts(ge->descript, str);

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

void graphic_engine_objects_at_space(Game *game, Id space_id, char *object)
{
  Space *space = NULL;
  Id obj_id = NO_ID;
  const char *names[MAX_OBJECTS];
  char tmp[OBJ_STR];
  int i;

  if (!game)
  {
    return;
  }

  if (space_id == NO_ID)
  {
    strcpy(object, " ");
    return;
  }

  space = game_get_space(game, space_id);
  if (!space)
  {
    return;
  }

  tmp[0] = '\0';
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    obj_id = space_get_objects_id(space, i);

    names[i] = game_get_object_name(game, obj_id);
    if (names[i] != NULL)
    {
      strcat(tmp, names[i]);
      strcat(tmp, " ");
    }
  }

  tmp[11] = '\0';

  strcpy(object, tmp);
}

void graphic_engine_character_at_space(Game *game, Id space_id, char *character_gdesc)
{
  Character *spider = NULL, *ant = NULL;
  const char *spider_gdesc = NULL, *ant_gdesc = NULL;
  Id spider_loc = NO_ID, ant_loc = NO_ID;

  spider = game_get_character_from_name(game, "Spider");
  ant = game_get_character_from_name(game, "Ant");

  spider_gdesc = game_get_character_gdesc(game, spider);
  spider_loc = game_get_character_location(game, spider);
  ant_gdesc = game_get_character_gdesc(game, ant);
  ant_loc = game_get_character_location(game, ant);

  if (spider_loc == space_id)
  {
    strcpy(character_gdesc, spider_gdesc);
  }
  else if (ant_loc == space_id)
  {
    strcpy(character_gdesc, ant_gdesc);
  }
  else
  {
    strcpy(character_gdesc, " ");
  }
}

Status print_spaces(Graphic_engine *ge, Game *game, Id space_id)
{
  Space *space_act = game_get_space(game, space_id);
  Id id_left = NO_ID, id_right = NO_ID;
  char obj_left[OBJ_STR], obj_act[OBJ_STR], obj_right[OBJ_STR];
  char left_border[SPACE_SIZE] = " ", act_border[SPACE_SIZE] = " ", right_border[SPACE_SIZE] = " ";
  char character_gdesc_act[G_SIZE], character_gdesc_left[G_SIZE], character_gdesc_right[G_SIZE];
  char str2_left[SPACE_SIZE] = " ", str2_act[SPACE_SIZE] = " ", str2_right[SPACE_SIZE] = " ";
  char str3_left[SPACE_SIZE] = " ", str3_act[SPACE_SIZE] = " ", str3_right[SPACE_SIZE] = " ";
  char space_gdesc_left[GD_HEIGHT][SPACE_SIZE], space_gdesc_act[GD_HEIGHT][SPACE_SIZE], space_gdesc_right[GD_HEIGHT][SPACE_SIZE];
  char player[] = "mO^";
  char str[255];
  int i;

  id_right = space_get_east(space_act);
  id_left = space_get_west(space_act);

  if (game_get_player_location(game) != space_id)
  {
    strcpy(player, " ");
  }

  for (i = 0; i < GD_HEIGHT; i++)
  {
    strcpy(space_gdesc_left[i], " ");
  }
  for (i = 0; i < GD_HEIGHT; i++)
  {
    strcpy(space_gdesc_act[i], " ");
  }
  for (i = 0; i < GD_HEIGHT; i++)
  {
    strcpy(space_gdesc_right[i], " ");
  }

  graphic_engine_objects_at_space(game, space_id, obj_act);
  graphic_engine_character_at_space(game, space_id, character_gdesc_act);
  graphic_engine_objects_at_space(game, id_left, obj_left);
  graphic_engine_character_at_space(game, id_left, character_gdesc_left);
  graphic_engine_objects_at_space(game, id_right, obj_right);
  graphic_engine_character_at_space(game, id_right, character_gdesc_right);

  if (space_id != NO_ID)
  {
    strcpy(act_border, " +---------------+ ");
    sprintf(str2_act, " | %3s %-6s %3d| ", player, character_gdesc_act, (int)space_id);
    for (i = 0; i < GD_HEIGHT; i++)
    {
      sprintf(space_gdesc_act[i], " |%-15s| ", game_get_space_gdesc(game, space_id, i));
    }
    sprintf(str3_act, " |%-15s| ", obj_act);
  }

  if (id_left != NO_ID)
  {
    strcpy(left_border, " +---------------+ ");
    sprintf(str2_left, " |     %-6s %3d| ", character_gdesc_left, (int)id_left);
    for (i = 0; i < GD_HEIGHT; i++)
    {
      sprintf(space_gdesc_left[i], " |%-15s| ", game_get_space_gdesc(game, id_left, i));
    }
    sprintf(str3_left, " |%-15s|<", obj_left);
  }

  if (id_right != NO_ID)
  {
    strcpy(right_border, " +---------------+ ");
    sprintf(str2_right, " |     %-6s %3d| ", character_gdesc_right, (int)id_right);
    for (i = 0; i < GD_HEIGHT; i++)
    {
      sprintf(space_gdesc_right[i], " |%-15s| ", game_get_space_gdesc(game, id_right, i));
    }
    sprintf(str3_right, ">|%-15s| ", obj_right);
  }

  sprintf(str, "%19s%19s%19s", left_border, act_border, right_border);
  screen_area_puts(ge->map, str);
  sprintf(str, "%19s%19s%19s", str2_left, str2_act, str2_right);
  screen_area_puts(ge->map, str);
  for (i = 0; i < GD_HEIGHT; i++)
  {
    sprintf(str, "%19s%19s%19s", space_gdesc_left[i], space_gdesc_act[i], space_gdesc_right[i]);
    screen_area_puts(ge->map, str);
  }
  sprintf(str, "%19s%19s%19s", str3_left, str3_act, str3_right);
  screen_area_puts(ge->map, str);
  sprintf(str, "%19s%19s%19s", left_border, act_border, right_border);
  screen_area_puts(ge->map, str);

  return OK;
}