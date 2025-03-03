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
    if (!set || id == NO_ID)
    {
        return ERROR;
    }
    /*If there is no more free space in the set structure return ERROR*/
    if (set->n_ids == MAX_SET)
    {
        return ERROR;
    }
    set->ids[set->n_ids] = id;
    set->n_ids++;

    return OK;
}

Status set_del(Set *set, Id id)
{
    int i, j;

    if (!set || id == NO_ID)
    {
        return ERROR;
    }

    for (i = 0; i < MAX_SET; i++)
    {
        if (set->ids[i] == id)
        {
            for (j = i; j < set->n_ids - 1; j++)
            {
                set->ids[j] = set->ids[j + 1];
            }
            set->n_ids--;
            return OK;
        }
    }

    /*If the given id does not appear in the set structure return ERROR*/
    return ERROR;
}

Id set_get_id(Set *set, int position)
{
    if (!set)
    {
        return NO_ID;
    }
    if (position < 0 || position > MAX_SET)
    {
        return NO_ID;
    }
    return set->ids[position];
}

int set_get_nids(Set *set)
{
    if (!set)
    {
        return -1;
    }
    return set->n_ids;
}

int set_get_position(Set *set, Id id)
{
    int i;
    if (!set)
    {
        return -1;
    }

    for (i = 0; i < MAX_SET; i++)
    {
        if (set->ids[i] == id)
        {
            return i;
        }
    }
    return -1;
}

Bool set_contains(Set *set, Id id)
{
    int i;
    if (!set || id == NO_ID)
    {
        return FALSE;
    }

    for (i = 0; i < MAX_SET; i++)
    {
        if (set->ids[i] == id)
        {
            return TRUE;
        }
    }
    return FALSE;
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

    return OK;
}