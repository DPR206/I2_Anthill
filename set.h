/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @author Claudia Saiz
 * @version 0
 * @date 18-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define MAX_SET 20

typedef struct _Set Set;

/**
 * @brief It creates a new set structure
 * @author Claudia Saiz
 *
 * @param ids pointer to an array with ids of the game
 * @return Set*, pointer to the new set
 */
Set *set_create();

/**
 * @brief It destroys a given set structure
 * @author Claudia Saiz
 *
 * @param set Pointer to the set to be destroyed
 * @return Status of the operation, OK if successful or ERROR if there was some mistake
 */
Status set_destroy(Set *set);

/**
 * @brief Adds a new id to the set structure
 * @author Claudia Saiz
 *
 * @param set Pointer to the set structure
 * @param id New id to be added
 * @return Status of the operation, OK if successful or ERROR if there was some mistake
 */
Status set_add(Set *set, Id id);

/**
 * @brief It deletes an id form the set structure
 * @author Claudia Saiz
 *
 * @param set Pointer to the set structure
 * @param id Id to be deleted from the set structure
 * @return Status of the operation, OK if successful or ERROR if there was some mistake
 */
Status set_del(Set *set, Id id);

/**
 * @brief It gets the id located in a given position of the array
 * @author Claudia Saiz
 *
 * @param set Pointer to the set structure
 * @param position Position of the id to get
 * @return Id located in the position
 */
Id set_get_id(Set *set, int position);

/**
 * @brief Gets the number of ids in the set structure
 * @author Claudia Saiz
 *
 * @param set Pointer to the set structure
 * @return int, number of ids
 */
int set_get_nids(Set *set);

/**
 * @brief It gets the position of a given id in the set structure
 * @author Claudia Saiz
 *
 * @param set Pointer to the set structure
 * @param id Id to search for in the set structure
 * @return int, position of the id, or -1 if the id is not found
 */
int set_get_position(Set *set, Id id);

/**
 * @brief it prints all the information of the set structure
 * @author Claudia Saiz
 *
 * @param set Pointer to the set structure
 * @return Status of the operation, OK if successful or ERROR if there was some mistake
 */
Status set_print(Set *set);

#endif