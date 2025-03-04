/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Duna Puente
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Duna Puente
 * 
 * @param id Identifier for the new player
 * @return Player*, a new player initialized
 */
Player *player_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Duna Puente
 * 
 * @param player 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player *player);

/**
 * @brief It gets the id of a player
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @return The id of the player
 */
Id player_get_id(Player *player);

/**
 * @brief It sets the name of a player
 * @author Duna Puente
 * 
 * @param player A pointer to the player whose name we are to set
 * @param name A string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player *player, char *name);

/**
 * @brief It gets the name of a space
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @return A string with the name of the player 
 */
const char *player_get_name(Player *player);

/**
 * @brief It sets the id of the object the player carries
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @param object The id of the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player *player, Id object);

/**
 * @brief It gets the id of the object the player carries
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @param object A pointer to the id of the object
 * @return The id of the object the player carries
 */
Id player_get_object(Player *player);

/**
 * @brief It sets the location of a player
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @param id The id of the location
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status player_set_location(Player *player, Id id);

/**
 * @brief It gets the player location
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @return The id of the player's location
 */
Id player_get_location (Player *player);

/**
 * @brief It prints the player information
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player *player);

/**
 * @brief It sets the player's life
 * @author Duna Puente
 * 
 * @param player A pointer to the player
 * @param life The player's lifes
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_life(Player *player, int life);

/**
 * @brief It gets the player's life
 * 
 * @param player A pointer to the player
 * @return The player's lifes
 */
int player_get_life(Player *player);

#endif
