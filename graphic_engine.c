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
 */
void graphic_engine_print_spaces(Graphic_engine *ge, Game *game, Id id_left, Id space_id, Id id_right);

/**
 * @brief It prints the location of all the objects in the descrition area
 * @author Claudia Saiz
 * 
 * @param ge Pointer to the graohic engine
 * @param game Pointer to the game
 */
void graphic_engine_print_objects_location(Graphic_engine *ge, Game *game);

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
  Id id_act = NO_ID, id_act_left=NO_ID, id_act_right=NO_ID;
  Id id_back = NO_ID, id_back_left=NO_ID, id_back_right=NO_ID;
  Id id_next_left=NO_ID, id_next = NO_ID, id_next_right=NO_ID;
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

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_act_left=space_get_west(space_act);
    id_act_right=space_get_east(space_act);

    if(id_back==NO_ID){
      id_back_left=space_get_north(game_get_space(game, id_act_left));
      id_back_right=space_get_north(game_get_space(game, id_act_right));
    } else {
      id_back_left=space_get_west(game_get_space(game, id_back));
      id_back_right=space_get_east(game_get_space(game, id_back));
    }
    graphic_engine_print_spaces(ge, game, id_back_left, id_back, id_back_right);
    if(id_back!=NO_ID){
      sprintf(str, "%28s^%28s", " ", " ");
      screen_area_puts(ge->map, str);
    }

    graphic_engine_print_spaces(ge, game, id_act_left, id_act, id_act_right);

    if(id_next!=NO_ID){
      sprintf(str, "%28sv%28s", " ", " ");
      screen_area_puts(ge->map, str);
    }
    if(id_next==NO_ID){
      id_next_left=space_get_south(game_get_space(game, id_act_left));
      id_next_right=space_get_south(game_get_space(game, id_act_right));
    } else {
      id_next_left=space_get_west(game_get_space(game, id_next));
      id_next_right=space_get_east(game_get_space(game, id_next));
    }
    graphic_engine_print_spaces(ge, game, id_next_left, id_next, id_next_right);
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
  graphic_engine_print_objects_location(ge, game);

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
      /*Si el string con el nombre de los objetos supera el espacio en el que se escriben, se escriben solo las letras que entren*/
      if((strlen(tmp)+strlen(names[i]))>=OBJ_STR){
        if(OBJ_STR-strlen(tmp)>0){
          strncat(tmp, names[i], OBJ_STR-strlen(tmp));
        }
      } else {
        strcat(tmp, names[i]);
        strcat(tmp, " ");
      }
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
  } else {
    strcpy(character_gdesc, " ");
  }
}

void graphic_engine_print_spaces(Graphic_engine *ge, Game *game, Id id_left, Id space_id, Id id_right)
{
  char obj_left[OBJ_STR], obj_act[OBJ_STR], obj_right[OBJ_STR];
  char left_border[SPACE_SIZE] = " ", act_border[SPACE_SIZE] = " ", right_border[SPACE_SIZE] = " ";
  char character_gdesc_act[G_SIZE], character_gdesc_left[G_SIZE], character_gdesc_right[G_SIZE];
  char str2_left[SPACE_SIZE] = " ", str2_act[SPACE_SIZE] = " ", str2_right[SPACE_SIZE] = " ";
  char str3_left[SPACE_SIZE] = " ", str3_act[SPACE_SIZE] = " ", str3_right[SPACE_SIZE] = " ";
  char space_gdesc_left[GD_HEIGHT][SPACE_SIZE], space_gdesc_act[GD_HEIGHT][SPACE_SIZE], space_gdesc_right[GD_HEIGHT][SPACE_SIZE];
  char player[] = "mO^";
  char left_arrow, right_arrow;
  char str[255];
  int i;

  if (game_get_player_location(game) != space_id)
  {
    strcpy(player, " ");
  }

  for(i=0; i<GD_HEIGHT; i++){
    strcpy(space_gdesc_left[i], " ");
  }
  for(i=0; i<GD_HEIGHT; i++){
    strcpy(space_gdesc_act[i], " ");
  }
  for(i=0; i<GD_HEIGHT; i++){
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
    sprintf(str2_act, " | %3s %-7s%3d| ", player, character_gdesc_act, (int)space_id);
    for(i=0; i<GD_HEIGHT; i++){
      sprintf(space_gdesc_act[i], " |%-15s| ", game_get_space_gdesc(game, space_id, i));
    }
    sprintf(str3_act, " |%-15s| ", obj_act);
  }

  if (id_left != NO_ID)
  {
    strcpy(left_border, " +---------------+ ");
    sprintf(str2_left, " |     %-7s%3d| ", character_gdesc_left, (int)id_left);
    for(i=0; i<GD_HEIGHT; i++){
      if((i==GD_HEIGHT/2)&&(space_id==game_get_player_location(game))){
        left_arrow='<';
      } else {
        left_arrow=' ';
      }
      sprintf(space_gdesc_left[i], " |%-15s|%c", game_get_space_gdesc(game, id_left, i), left_arrow);
    }
    sprintf(str3_left, " |%-15s| ", obj_left);
  }

  if (id_right != NO_ID)
  {
    strcpy(right_border, " +---------------+ ");
    sprintf(str2_right, " |     %-7s%3d| ", character_gdesc_right, (int)id_right);
    for(i=0; i<GD_HEIGHT; i++){
      if((i==GD_HEIGHT/2)&&(space_id==game_get_player_location(game))){
        right_arrow='>';
      } else {
        right_arrow=' ';
      }
      sprintf(space_gdesc_right[i], "%c|%-15s| ", right_arrow, game_get_space_gdesc(game, id_right, i));
    }
    sprintf(str3_right, " |%-15s| ", obj_right);
  }

  sprintf(str, "%19s%19s%19s", left_border, act_border, right_border);
  screen_area_puts(ge->map, str);
  sprintf(str, "%19s%19s%19s", str2_left, str2_act, str2_right);
  screen_area_puts(ge->map, str);
  for (i=0; i<GD_HEIGHT; i++){
    sprintf(str, "%19s%19s%19s", space_gdesc_left[i], space_gdesc_act[i], space_gdesc_right[i]);
    screen_area_puts(ge->map, str);
  }
  sprintf(str, "%19s%19s%19s", str3_left, str3_act, str3_right);
  screen_area_puts(ge->map, str);
  sprintf(str, "%19s%19s%19s", left_border, act_border, right_border);
  screen_area_puts(ge->map, str);
}

void graphic_engine_print_objects_location(Graphic_engine *ge, Game *game){
  int i;
  Id object_id=NO_ID, object_loc=NO_ID;
  const char *object_name=NULL;
  char str[255];

  for(i=0; i<game_get_n_objects(game); i++){
    object_id=game_get_object_id_from_position(game, i);
    object_name=game_get_object_name(game, object_id);
    object_loc=game_get_object_location(game, object_id);

    if(object_loc==NO_ID){
      sprintf(str, "  %s with player", object_name);
      screen_area_puts(ge->descript, str);
    } else {
      sprintf(str, "  %s:%d", object_name, (int)object_loc);
      screen_area_puts(ge->descript, str);
    }
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
}