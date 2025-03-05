/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"
#include "character.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space *space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space *space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space *space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space *space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space *space);

/**
 * @brief It sets the Id of the object to the set structure of the space
 * @author Claudia Saiz
 *
 * @param space a pointer to the space
 * @param value Id of the object in the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_object(Space *space, Id object);

/**
 * @brief It gets the set structure of the objects in the space
 * @author Claudia Saiz
 *
 * @param space a pointer to the space
 * @return Set structure with ids of the objects in the space, or NULL if there was some mistake
 */
Set *space_get_objects(Space *space);

/**
 * @brief It adds the id of an object to the set structure of the space
 * @author Claudia Saiz
 *
 * @param space a pointer to the space
 * @param object id of the object to add
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space *space, Id object);

/**
 * @brief It gets the id number of an object given its position in the set structure of a space
 * @author Claudia Saiz
 *
 * @param space a pointer to the space
 * @param position of the id to get in the set structure
 * @return Id number of the object
 */
Id space_get_objects_id(Space *space, int position);

/**
 * @brief It gets whether there is an object id in the space
 * @author Claudia Saiz
 *
 * @param space Pointer to the space
 * @param object Id of the object to search for
 * @return Bool, TRUE if the object is in the space, FALSE if not
 */
Bool space_at_object(Space *space, Id object);

/**
 * @brief It sets a character in the space given
 * @author Claudia Saiz
 * 
 * @param space Pointer to the space
 * @param character Pointer to the character
 * @return Status of the operation, OK if successful, or ERROR if not
 */
Status space_set_character(Space *space, Character *character);

/**
 * @brief It prints the space information
 * @author Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space *space);

#endif
