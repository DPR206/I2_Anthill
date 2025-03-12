/**
 * @brief It implements the character module
 * 
 * @file character.c 
 * @author Duna Puente
 * @version 0
 * @date 03-03-2025
 * @copyright GNU Public License
 * 
 */
#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define G_SIZE 7

/**
 * @brief Character
 * 
 * This struct stores all the information of character
 * 
 */
struct _Character
{
    Id id;
    char name[WORD_SIZE+1];
    char gdec[G_SIZE];
    int health;
    Bool friendly;
    char message[WORD_SIZE];
};

Character *character_create()
{
    Character *character=NULL;

    character=(Character *)calloc(1, sizeof(Character));

    /* Error control */
    if (!character)
    {
        return NULL;
    }

    /* Initializing new character */
    character_set_id(character, NO_ID);
    character_set_name(character, "\0");
    character_set_health(character, 0);
    character_set_friendly(character, FALSE);
    character_set_message(character, "\0");
    
    return character;
}

Status character_destroy(Character *character)
{
    /* Error control */
    if (!character)
    {
        return ERROR;
    } else {
        free(character);
    }
    
    return OK;
}

Status character_set_id(Character *character, Id id)
{
    /* Error control */
    if (!character)
    {
        return ERROR;
    }

    character->id=id;

    return OK;
    
}

Id character_get_id(Character *character) 
{ 
    /* Error control */
    if (!character)
    {
        return NO_ID;
    }
    
    return character->id; 
}

Status character_set_name(Character *character, char *name)
{
    /* Error control */
    if (!character || !name || strlen(name)>WORD_SIZE)
    {
        return ERROR;
    }

    strcpy(character->name, name);

    return OK;
    
}

const char *character_get_name(Character *character) 
{ 
    /* Error control */
    if (!character)
    {
        return NULL;
    }
    
    return character->name; 
}

Status character_set_gdesc(Character *character, char *gdesc)
{
    /* Error control */
    if (!character || !gdesc || strlen(gdesc)>G_SIZE)
    {
        return ERROR;
    }

    strcpy(character->gdec, gdesc);

    return OK;
    
}

const char *character_get_gdesc(Character *character) 
{ 
    /* Error control */
    if (!character)
    {
        return NULL;
    }
    
    return character->gdec; 
}

Status character_set_health(Character *character, int health)
{
    /* Error control */
    if (!character)
    {
        return ERROR;
    }

    character->health=health;

    return OK;
    
}

int character_get_health(Character *character) 
{ 
    /* Error control */
    if (!character)
    {
        return -1;
    }
    
    return character->health; 
}

Status character_set_friendly(Character *character, Bool friendly)
{
    /* Error control */
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
    /* Error control */
    if (!character || !message)
    {
        return ERROR;
    }

    strcpy(character->message, message);

    return OK;
    
}

char *character_get_message(Character *character) 
{ 
    /* Error control */
    if (!character)
    {
        return NULL;
    }
    
    return character->message; 
}
