#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

Character *character_create();

Status character_destroy(Character *character);

Status character_set_id(Character *character, Id id);

Id character_get_id(Character *chartacer);

Status character_set_name(Character *character, char *name);

const char *character_get_name(Character *character);

Status character_set_gdesc(Character *character, char *gdesc);

const char *character_get_gdesc(Character *character);

Status character_set_salud(Character *character, int salud);

int character_get_salud(Character *character);

Status character_set_friendly(Character *character, Bool friendly);

Bool character_get_friendly(Character *character);

Status character_set_message(Character *character, char *message);

#endif
