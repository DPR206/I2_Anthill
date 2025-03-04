/**
 * @brief It defines the character module interface
 *
 * @file character.h
 * @author Duna Puente
 * @version 0
 * @date 03-03-2025
 * @copyright GNU Public License
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

/**
 * @brief It creates a new character
 * @author Duna Puente
 * 
 * @return A pointer to the new character
 */
Character *character_create();

/**
 * @brief It destroys a character
 * 
 * @param character A pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status character_destroy(Character *character);

/**
 * @brief It sets the character id
 * @author Duna Puente
 * 
 * @param character A pointer to the character 
 * @param id The new id of the character
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status character_set_id(Character *character, Id id);

/**
 * @brief It gets the character's id
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @return Id, the id of the character
 */
Id character_get_id(Character *character);

/**
 * @brief It sets the character's name
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @param name A pointer to the string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake  
 */
Status character_set_name(Character *character, char *name);

/**
 * @brief It gets the character's name
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @return A pointer to the string with the name of the character
 */
const char *character_get_name(Character *character);

/**
 * @brief It sets the character's description
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @param gdesc A pointer to the string of the descrition to store
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status character_set_gdesc(Character *character, char *gdesc);

/**
 * @brief It gets the character's description
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @return A pointer to the string with the description 
 */
const char *character_get_gdesc(Character *character);

/**
 * @brief It sets the character's health
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @param salud The amount of health
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_salud(Character *character, int salud);

/**
 * @brief It gets the character's health
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @return The character's health
 */
int character_get_salud(Character *character);

/**
 * @brief It sets if the character is friendly or not
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @param friendly The friendliness of the character
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status character_set_friendly(Character *character, Bool friendly);

/**
 * @brief It gets if the character is friendly or not
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @return Bool, TRUE if the character is a friend, FALSE if it's an enemy
 */
Bool character_get_friendly(Character *character);

/**
 * @brief It sets the character's message
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @param message A pointer to the string with the message to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_message(Character *character, char *message);

/**
 * @brief It gets the character's message
 * @author Duna Puente
 * 
 * @param character A pointer to the character
 * @return A pointer to the string with the character's message
 */
const char *character_get_message(Character *character);

#endif
