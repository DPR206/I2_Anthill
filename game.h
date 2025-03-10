/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "character.h"

#define MAX_SPACES 100
#define MAX_OBJECTS 4
#define MAX_CHARACTERS 10

typedef struct _Game Game;



/*Funciones de tipo game*/

/**
 * @brief It creates a new game, initializing all its members
 * @author Duna Puente
 *
 * @param game Pointer to the game to initialize
 * @return Status of the operation: OK if successful
 */
Game *game_create();

/**
 * @brief creates a new game from a file, loads spaces from a specified file, and sets the initial player and object locations to the first space
 * @author Claudia Saiz
 *
 * @param game Pointer to the game to initialize
 * @param filename Name of the file with the space data
 * @return Status of the operation: ERROR if initialization fails, OK if successful
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief It gets whether the game is finished or not
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 * @return The state of the game: TRUE if finished, FALSE if not
 */
Bool game_get_finished(Game *game);

/**
 * @brief It updates whether the game is finished or not
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 * @param finished The new finished state to set
 * @return Status of the operation: OK if succesful
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief It prints information about the current game
 * @author Duna Puente
 *
 * @param game Pointer to the game
 */
void game_print(Game *game);

/**
 * @brief Destroys a game structure, free the memory of all spaces and the last command
 * @author Duna Puente
 *
 * @param game Pointer to the game to destroy
 * @return Status of the operation: OK if successful
 */
Status game_destroy(Game *game);

/**
 * @brief It sets the game's last message
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param message A strig with the last message
 * @return Status of the operation: OK if successful
 */
Status game_set_last_message(Game *game, char *message);



/*Funciones de tipo game_space*/

/**
 * @brief It creates a new game space, allocating memory and initializing its members
 * @author Duna Puente
 * 
 * @param game Pointer to the game we want to create
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_createspace(Game *game);

/**
 * @brief It adds a space to the games space array
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param space Pointer to the space to add
 * @return Status of the operation: ERROR if failes, OK if successful 
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It gets a space from the game by its Id
 * @author Duna Puente
 *
 * @param game Pointer to game
 * @param id The Id of the space to return
 * @return Pointer to the space, or NULL if the space is not found.
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets the number of spaces in the game->spaces array
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @return int, number of spaces
 */
int game_get_numspaces(Game *game);

/**
 * @brief It adds one to the number of spaces in the game
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @return Status of the operation, OK if successful, ERROR if not
 */
Status game_add_numspaces(Game *game);

/**
 * @brief It adds a new space to the game->spaces array
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param space Pointer to the space to be added
 * @return Status of the operation, OK if successful, ERROR if not
 */
Status game_add_newspace(Game *game, Space *space);



/*Funciones de tipo game_player*/

/**
 * @brief It gets the id of the space where the player is located
 * @author Duna Puente
 *
 * @param game Pointer to game
 * @return Id, the players current location
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets the players location to a specific ID
 * @author Duna Puente
 *
 * @param game Pointer to the game
 * @param id The new space ID where the player will be located
 * @return Status of the operation: ERROR if no ID, OK if successful
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It gets the health of the player
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @return int, health of the player
 */
int game_get_player_health(Game *game);

/**
 * @brief It adds the player to the game
 * @author Claudia Saiz
 * 
 * @param game POinter to the game
 * @return Status of the operation, OK id successful or ERROR if not
 */
Status game_add_player(Game *game);

/**
 * @brief It gets the id of the object the player is carrying
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @return Id of the object the player carries, or NO_ID if it doesnt carry an object or there is any problem
 */
Id game_player_get_object(Game *game);

/**
 * @brief It sets the id of the object that the player is carrying
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param id Id of the object to be set
 * @return Status of the operation, OK id successful or ERROR if not 
 */
Status game_player_set_object(Game *game, Id id);

/**
 * @brief It sets the player's health
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param health The health of the player
 * @return Status of the operation, OK id successful or ERROR if not  
 */
Status game_player_set_health(Game *game, int health);



/*Funciones de tipo game_object*/

/**
 * @brief It gets the ID of the space where an object is located by its identifier
 * @author Duna Puente
 *
 * @param game Pointer to the game
 * @param id Id of the object to search for
 * @return The objects location ID
 */
Id game_get_object_location(Game *game, Id object);

/**
 * @brief It gets the location of an object from its name
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param object Name of the object
 * @return Id of the object
 */
Id game_get_object_location_from_name(Game *game, char *object);

/**
 * @brief It gets the name of an object from its id
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param object Id of the object
 * @return const char*, name of the object
 */
const char *game_get_object_name(Game *game, Id object);

/**
 * @brief It returns an object's id
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param object Name of the object
 * @return Id, the id of the object
 */
Id game_get_object_id_from_name(Game *game, char *object);

/**
 * @brief It sets the objects location to a specific ID
 * @author Duna Puente
 *
 * @param game Pointer to the game
 * @param id The new space ID where the object will be located
 * @return Status of the operation: ERROR if no ID, OK if successful
 */
Status game_set_object_location(Game *game, Id object, Id location);

/**
 * @brief It adds an object to the object array of the game
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param object Pointer to the object
 * @return Status of the operation: ERROR if failes, OK if successful 
 */
Status game_add_object(Game *game, Object *object);



/*Funciones de tipo game_command*/

/**
 * @brief It gets the last command executed
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 * @return Pointer to the last command executed
 */
Command *game_get_last_command(Game *game);

/**
 * @brief It sets the last command to the provided command
 * @author Profesores PPROG
 *
 * @param game Pointer to the game
 * @param command Pointer to the command to set
 * @return Status of the operation: OK if succesful
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It gets the status of the last command executed
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @return char, Status of the last command executed
 */
const char *game_get_last_command_status(Game *game);

/**
 * @brief It sets the last command status to the provided status
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param const char* status to be set
 * @return Status of the operation, OK if successful or ERROR if not
 */
Status game_set_last_command_status(Game *game, char *status);



/*Funciones de tipo game_character*/

/**
 * @brief It adds a character to the character array of the game
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param character Pointer to the character
 * @return Status of the operation: ERROR if failes, OK if successful 
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief It gets the graphic description of a character from its name
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param character Name of the character 
 * @return char*, graphic descrition of the character
 */
const char *game_get_character_gdesc(Game *game, char *character);

/**
 * @brief It gets the location of a character from its name
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param character Name of the character
 * @return Id, location of the character
 */
Id game_get_character_location_from_name(Game *game, char *character);

/**
 * @brief It gets the location of a character from its id
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param character Id of the character
 * @return Id, location of the character
 */
Id game_get_character_location(Game *game, Id character);

/**
 * @brief It gets the health of a character fron its name
 * @author Claudia Saiz
 * 
 * @param game Pointer to the game
 * @param character Name of the character
 * @return int, Health of the character
 */
int game_get_character_health(Game *game, char *character);

/**
 * @brief It gets the a character's id
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param character Name of the character
 * @return Id, the character's id 
 */
Id game_get_character_id(Game *game, char *character);

/**
 * @brief It returns whether the character is friendly or not
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param character Name of the character
 * @return Bool, if the character is friendly or not
 */
Bool game_get_charatcter_friendly(Game *game, char *character);

/**
 * @brief It returns a character's message
 * @author Duna Puente
 * 
 * @param game Pointer to the game
 * @param character Name of the character
 * @return A string with the character's message
 */
char *game_get_character_message(Game *game, char *character);

/**
 * @brief It sets the character's health
 * 
 * @param game Pointer to the game
 * @param character Name of the character
 * @param health The health of the character
 * @return Status of the operation: ERROR if failes, OK if successful 
 */
Status game_character_set_health(Game *game, char *character, int health);

/**
 * @brief It gets the name of the character in a space
 * @author Duna Puente
 * 
 * @param game Pointer to a game
 * @return A string with the name of the character 
 */
char *game_space_get_character_name(Game *game);

#endif