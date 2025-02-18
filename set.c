/**
 * @brief It implements the set module
 *
 * @file set.c
 * @author Claudia Saiz
 * @version 0
 * @date 18-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "set.h"

/**
 * @brief This struct contains all ids in a game and the number of them
 *
 */
struct _Set
{
    Id ids[MAX_SET];
    int n_ids;
};

Set *set_create()
{
    int i;
    Set *newSet = NULL;

    newSet = (Set *)malloc(sizeof(Set));
    if (!newSet)
    {
        return NULL;
    }

    /*Initialize n_ids to 0 and all ids to NO_ID*/
    newSet->n_ids = 0;
    for (i = 0; i < MAX_SET; i++)
    {
        newSet->ids[i] = NO_ID;
    }

    return newSet;
}

Status set_destroy(Set *set)
{
    if (!set)
    {
        return ERROR;
    }
    free(set);
    return OK;
}

Status set_add(Set *set, Id id)
{
    int i = 0;

    if (!set || id == NO_ID)
    {
        return ERROR;
    }
    for (i = 0; i < MAX_SET; i++)
    {
        if (set->ids[i] == NO_ID)
        {
            set->ids[i] = id;
            set->n_ids++;
            return OK;
        }
    }

    /*If there is no more free space in the set structure return ERROR*/
    return ERROR;
}

Status set_del(Set *set, Id id)
{
    int i, position = MAX_SET;

    if (!set || id == NO_ID)
    {
        return ERROR;
    }

    for (i = 0; i < MAX_SET; i++)
    {
        if (set->ids[i] == id)
        {
            set->ids[i] = NO_ID;
            set->n_ids--;
            return OK;
        }
    }

    /*If the given id does not appear in the set structure return ERROR*/
    return ERROR;
}

Status set_print(Set *set)
{
    int i;

    if (!set)
    {
        return ERROR;
    }

    fprintf(stdout, "-> Set(");
    for (i = 0; i < set->n_ids; i++)
    {
        fprintf(stdout, "Id %d: %ld;", i + 1, set->ids[i]);
    }
    fprintf(stdout, "Number of ids: %d)\n", set->n_ids);
}