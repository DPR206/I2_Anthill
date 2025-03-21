/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 2
 * @date 05-03-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
  Id id;                                /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];             /*!< Name of the space */
  Id north;                             /*!< Id of the space at the north */
  Id south;                             /*!< Id of the space at the south */
  Id east;                              /*!< Id of the space at the east */
  Id west;                              /*!< Id of the space at the west */
  Set *objects;                         /*!< Set containing ids of the objects in the space*/
  Character *character;                 /*!< Character in the space*/
  char gdesc[GD_HEIGHT][GD_WIDTH + 1];  /*!< Graphic description of the space */
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space *space_create(Id id)
{
  Space *newSpace = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *)malloc(sizeof(Space));
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();
  newSpace->character= NULL;
  newSpace->gdesc[0][0]='\0';

  return newSpace;
}

Status space_destroy(Space *space)
{
  if (!space)
  {
    return ERROR;
  }
  set_destroy(space->objects);
  free(space);
  return OK;
}

Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->west;
}

Status space_set_object(Space *space, Id object)
{
  if (!space || object == NO_ID)
  {
    return ERROR;
  }
  if(set_add(space->objects, object)==ERROR) {return ERROR;}
  return OK;
}

Set *space_get_objects(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->objects;
}

Status space_add_object(Space *space, Id object)
{
  if (!space || object == NO_ID || !space->objects)
  {
    return ERROR;
  }
  set_add(space->objects, object);
  return OK;
}

Id space_get_objects_id(Space *space, int position)
{
  if (!space)
  {
    return NO_ID;
  }
  return set_get_id(space->objects, position);
}

Bool space_at_object(Space *space, Id object)
{
  if (!space)
  {
    return FALSE;
  }
  if (set_get_position(space->objects, object) >= 0)
  {
    return TRUE;
  }
  return FALSE;
}

Status space_set_character(Space *space, Character *character)
{
  if (!space || !character)
  {
    return ERROR;
  }
  space->character=character;
  return OK;
}

Character *space_get_character(Space *space){
  if(!space){
    return NULL;
  }
  return space->character;
}

Status space_set_gdesc(Space *space, char gdesc[GD_HEIGHT][GD_WIDTH + 1])
{
  int i;

  if (!space)
  {
    return ERROR;
  }

  for(i=0; i<GD_HEIGHT; i++){
    strcpy(space->gdesc[i], gdesc[i]);
  }
  
  return OK; 
}

char *space_get_gdesc(Space *space, int line)
{
  if (!space)
  {
    return NULL;
  }

  return space->gdesc[line];
}

Status space_print(Space *space) /*¿hay que cambiar algo para gdesc?*/
{
  Id idaux = NO_ID;

  /* Error Control */
  if (!space)
  {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  if (space_get_objects(space) != NULL)
  {
    fprintf(stdout, "---> Objects in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> No objects in the space.\n");
  }

  return OK;
}

Status space_set_del(Space *space, Id id)
{
  /* Error control */
  if (!space)
  {
    return ERROR;
  }

  set_del(space->objects, id);
  
  return OK;
}
