/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief This struct contains all the areas of the game screen
 *
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Creates and initializes the garphic engine. Initializes the screen size and creates other areas for the game display
 * @author Profesores PPROG
 *
 * @return Graphic_engine*, pointer to the created graphic engine or NULL if allocation fails
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Destroys all the areas created and frees the memory asociated to the graphic engine
 * @author Profesores PPROG
 *
 * @param ge The graphic engine to be destroyed
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Paints the map, description, banner, help and feedback areas on the screen
 * @author Profesores PPROG
 *
 * @param ge The graphic engine being used for the game
 * @param game Pointer to the current game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
