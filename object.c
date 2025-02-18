/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Claudia Saiz
 * @version 0
 * @date 05-02-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This struct contains all the information of an object
 * 
 */
struct _Object {
  Id id;
  char name[WORD_SIZE + 1];
};

Object* object_create(Id id){
  Object *newObject=NULL;

  /* Error Control */
  if (id == NO_ID) return NULL;

  newObject = (Object*)malloc(sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  /* Initialization of new object*/
  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}

Status object_destroy(Object* object){
  
  /* Error Control */
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

Status object_set_id(Object *object, Id id)
{
  /* Error Control */
  if ( !object )
  {
      return ERROR;
  }

  object->id=id;

  return OK;
}

Id object_get_id(Object* object){
  
  /* Error Control */
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

Status object_set_name(Object* object, char* name){
  
  /* Error Control */
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* object_get_name(Object* object){
  
  /* Error Control */
  if (!object) {
    return NULL;
  }
  return object->name;
}

Status object_print(Object* object){

  /* Error Control */
  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
