/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_reader.h"
#include "game_actions.h"
#include "graphic_engine.h"

/**
 * @brief It initializes the game loop, by initializing the game from a file and setting up the graphic engine
 * @author Profesores PPROG
 *
 * @param game Pointer to the game to initialize
 * @param gengine Pointer to the graphic engine to initialize
 * @param file_name The name of the file with the game data
 * @return int, 0 if sucessful, or 1 if there is an error
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief It runs the main game loop and calls functions to continuously update the agem state until the game is finished or the exit command is given
 * @author Profesores PPROG
 *
 * @param game The current game state
 * @param gengine The graphic engine being used for the current game
 */
void game_loop_run(Game game, Graphic_engine *gengine);

/**
 * @brief Destroys the game and the graphic engine after the game loop finishes
 * @author Profesores PPROG
 *
 * @param game Game to be destroyed
 * @param gengine Graphic engine to be destroyed
 */
void game_loop_cleanup(Game game, Graphic_engine *gengine);

/**
 * @brief Initializes the game loop, then runs the game loop
 * @author Profesores PPROG
 *
 * @param argc Number of arguments passed to the function
 * @param argv Pointer to array where the arguments are stored as strings
 * @return int, 0 if sucessful, or 1 if there is an error in initialization
 */
int main(int argc, char *argv[])
{
  Game game;
  Graphic_engine *gengine;

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game game, Graphic_engine *gengine)
{
  Command *last_cmd;

  if (!gengine)
  {
    return;
  }

  last_cmd = game_get_last_command(&game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(&game) == FALSE))
  {
    graphic_engine_paint_game(gengine, &game);
    command_get_user_input(last_cmd);
    game_actions_update(&game, last_cmd);
  }

  free(last_cmd);
}

void game_loop_cleanup(Game game, Graphic_engine *gengine)
{
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
