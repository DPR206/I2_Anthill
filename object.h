/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Claudia Saiz
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/**
 * @brief It creates a new object, allocating memory and initializing its members
 * @author Claudia Saiz
 *
 * @param id identifier for the new object
 * @return Object*, a new object initialized
 */
Object *object_create(Id id);

/**
 * @brief It destroys an object, freeing the allocated memory
 * @author Claudia Saiz
 *
 * @param object Pointer to the object to be destroyed
 * @return Status of the operation, OK if sucessful or ERROR if there is some mistake
 */
Status object_destroy(Object *object);

/**
 * @brief It sets the id of an object
 * @author Claudia Saiz
 * 
 * @param object Pointer to the object
 * @param id The id to be set
 * @return Status of the operation, OK if sucessful or ERROR if there is some mistake 
 */
Status object_set_id(Object *object, Id id);

/**
 * @brief It gets the id of an object
 * @author Claudia Saiz
 *
 * @param object Pointer to the object
 * @return Id of the object
 */
Id object_get_id(Object *object);

/**
 * @brief It sets the name of an object
 * @author Claudia Saiz
 *
 * @param object Pointer to the object
 * @param name String with the name
 * @return Status of the operation, OK if sucessful or ERROR if there is some mistake
 */
Status object_set_name(Object *object, char *name);

/**
 * @brief It gets the name of an object
 * @author Claudia Saiz
 *
 * @param object Pointer to the object
 * @return const char*, a string with the name of the object
 */
const char *object_get_name(Object *object);

/**
 * @brief It prints the object information
 * @author Claudia Saiz
 *
 * @param object Pointer to the object
 * @return Status of the operation, OK if sucessful or ERROR if there is some mistake
 */
Status object_print(Object *object);

#endif
