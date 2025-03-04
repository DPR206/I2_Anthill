#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define G_SIZE 7

struct _Character
{
    Id id;
    char name[WORD_SIZE+1];
    char gdec[G_SIZE];
    int salud;
    Bool friendly;
    char message[WORD_SIZE];
};

Character *character_create()
{
    Character *character=NULL;

    character=(Character *)calloc(1, sizeof(Character));

    if (!character)
    {
        return NULL;
    }

    character_set_id(character, NO_ID);
    character_set_name(character, "\0");
    character_set_salud(character, 0);
    character_set_friendly(character, FALSE);
    charcter_set_message(character, "\0");
    
    return character;
}

Status character_destroy(Character *character)
{
    if (!character)
    {
        return ERROR;
    } else {
        free(character->name);
        free(character->gdec);
        free(character->message);
        free(character);
    }
    
    return OK;
}

Status character_set_id(Character *character, Id id)
{
    if (!character)
    {
        return ERROR;
    }

    character->id=id;

    return OK;
    
}

Id character_get_id(Character *character) { return character->id; }

Status character_set_name(Character *character, char *name)
{
    if (!character || !name || strlen(name)>WORD_SIZE)
    {
        return ERROR;
    }

    strcpy(character->name, name);

    return OK;
    
}

const char *character_get_name(Character *character) { return character->name; }

Status character_set_gdesc(Character *character, char *gdesc)
{
    if (!character || !gdesc || gdesc>G_SIZE)
    {
        return ERROR;
    }

    strcpy(character->gdec, gdesc);

    return OK;
    
}

const char *character_get_gdesc(Character *character) { return character->gdec; }

Status character_set_salud(Character *character, int salud)
{
    if (!character)
    {
        return ERROR;
    }

    character->salud=salud;

    return OK;
    
}

int character_get_salud(Character *character) { return character->salud; }

Status character_set_friendly(Character *character, Bool friendly)
{
    if (!character)
    {
        return ERROR;
    }
    
    character->friendly=friendly;

    return OK;
    
}

Bool character_get_friendly(Character *character) { return character->friendly; }

Status character_set_message(Character *character, char *message)
{
    if (!character || !message)
    {
        return ERROR;
    }

    strcpy(character->message, message);

    return OK;
    
}

const char *character_get_message(Character *character) { return character->message; }
