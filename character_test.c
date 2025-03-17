/**
 * @brief It tests set module
 *
 * @file character_test.c
 * @author Duna Puente
 * @version 1
 * @date 28-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "test.h"
#include "character_test.h"

#define MAX_TESTS 40

/**
 * @brief Main function for Character unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all test for module Character:\n");
    }
    else
    {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS)
        {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1)
        test1_character_create();
    if (all || test == 2)
        test2_character_create();
    if (all || test == 3)
        test1_character_destroy();
    if (all || test == 4)
        test2_character_destroy();
    if (all || test == 5)
        test1_character_setid();
    if (all || test == 6)
        test2_character_setid();
    if (all || test == 7)
        test1_character_get_id();
    if (all || test == 8)
        test2_character_get_id();
    if (all || test == 9)
        test1_character_set_name();
    if (all || test == 10)
        test2_character_set_name();
    if (all || test == 11)
        test1_character_get_name();
    if (all || test == 12)
        test2_character_get_name();
    if (all || test == 13)
        test1_character_set_gdesc();
    if (all || test == 14)
        test2_character_set_gdesc();
    if (all || test == 15)
        test1_character_get_gdesc();
    if (all || test == 16)
        test2_character_get_gdesc();
    if (all || test == 17)
        test1_character_set_health();
    if (all || test == 18)
        test2_character_set_health();
    if (all || test == 19)
        test1_character_get_health();
    if (all || test == 20)
        test2_character_get_health();
    if (all || test == 21)
        test1_character_set_friendly();
    if (all || test == 22)
        test2_character_set_friendly();
    if (all || test == 23)
        test1_character_get_friendly();
    if (all || test == 24)
        test2_character_get_friendly();
    if (all || test == 25)
        test1_character_set_message();
    if (all || test == 26)
        test2_character_set_message();
    if (all || test == 27)
        test1_character_get_message();
    if (all || test == 28)
        test2_character_get_message();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_character_create()
{
    Character *character = NULL;
    int result;
    character = character_create(),
    result = (character != NULL);
    PRINT_TEST_RESULT(result);
    character_destroy(character);
}

void test2_character_create()
{
    Character *character = NULL;
    character = character_create();
    PRINT_TEST_RESULT(character_get_id(character) == NO_ID);
    character_destroy(character);
}

void test1_character_destroy()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_destroy(character) == ERROR);
}

void test2_character_destroy()
{
    Character *character = NULL;
    character = character_create();
    PRINT_TEST_RESULT(character_destroy(character) == OK);
}

void test1_character_setid()
{
    Character *character = NULL;
    Id id = 1;
    PRINT_TEST_RESULT(character_set_id(character, id) == ERROR);
}

void test2_character_setid()
{
    Character *character = NULL;
    Id id = 1;
    character = character_create();
    PRINT_TEST_RESULT(character_set_id(character, id) == OK);
    character_destroy(character);
}

void test1_character_get_id()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_id(character) == NO_ID);
}

void test2_character_get_id()
{
    Character *character = NULL;
    Id id = 1;
    character = character_create();
    character_set_id(character, id);
    PRINT_TEST_RESULT(character_get_id(character) != NO_ID);
    character_destroy(character);
}

void test1_character_set_name()
{
    Character *character = NULL;
    char name[] = "ant";
    PRINT_TEST_RESULT(character_set_name(character, name) == ERROR);
}

void test2_character_set_name()
{
    Character *character = NULL;
    char name[] = "ant";
    character = character_create();
    PRINT_TEST_RESULT(character_set_name(character, name) == OK);
    character_destroy(character);
}

void test1_character_get_name()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_name(character) == NULL);
}

void test2_character_get_name()
{
    Character *character = NULL;
    character = character_create();
    PRINT_TEST_RESULT(character_get_name(character) != NULL);
    character_destroy(character);
}

void test1_character_set_gdesc()
{
    Character *character = NULL;
    char gdesc[] = "test";
    PRINT_TEST_RESULT(character_set_gdesc(character, gdesc) == ERROR);
}

void test2_character_set_gdesc()
{
    Character *character = NULL;
    char gdesc[] = "test";
    character = character_create();
    PRINT_TEST_RESULT(character_set_gdesc(character, gdesc) == OK);
    character_destroy(character);
}

void test1_character_get_gdesc()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_gdesc(character) == NULL);
}

void test2_character_get_gdesc()
{
    Character *character = NULL;
    character = character_create();
    PRINT_TEST_RESULT(character_get_gdesc(character) != NULL);
    character_destroy(character);
}

void test1_character_set_health()
{
    Character *character = NULL;
    int health = 5;
    PRINT_TEST_RESULT(character_set_health(character, health) == ERROR);
}

void test2_character_set_health()
{
    Character *character = NULL;
    int health = 5;
    character = character_create();
    PRINT_TEST_RESULT(character_set_health(character, health) == OK);
    character_destroy(character);
}

void test1_character_get_health()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_health(character) == -1);
}

void test2_character_get_health()
{
    Character *character = NULL;
    character = character_create();
    PRINT_TEST_RESULT(character_get_health(character) != -1);
    character_destroy(character);
}

void test1_character_set_friendly()
{
    Character *character = NULL;
    Bool friendly = TRUE;
    PRINT_TEST_RESULT(character_set_friendly(character, friendly) == ERROR);
}

void test2_character_set_friendly()
{
    Character *character = NULL;
    Bool friendly = TRUE;
    character = character_create();
    PRINT_TEST_RESULT(character_set_friendly(character, friendly) == OK);
    character_destroy(character);
}

void test1_character_get_friendly()
{
    Character *character = NULL;
    Bool friendly = TRUE;
    character = character_create();
    character_set_friendly(character, friendly);
    PRINT_TEST_RESULT(character_get_friendly(character) == TRUE);
    character_destroy(character);
}

void test2_character_get_friendly()
{
    Character *character = NULL;
    Bool friendly = FALSE;
    character = character_create();
    character_set_friendly(character, friendly);
    PRINT_TEST_RESULT(character_get_friendly(character) == FALSE);
    character_destroy(character);
}

void test1_character_set_message()
{
    Character *character = NULL;
    char message[] = "Hi!";
    PRINT_TEST_RESULT(character_set_message(character, message) == ERROR);
}

void test2_character_set_message()
{
    Character *character = NULL;
    char message[] = "Hi!";
    character = character_create();
    PRINT_TEST_RESULT(character_set_message(character, message) == OK);
    character_destroy(character);
}

void test1_character_get_message()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_message(character) == NULL);
}

void test2_character_get_message()
{
    Character *character = NULL;
    character = character_create();
    PRINT_TEST_RESULT(character_get_message(character) != NULL);
    character_create(character);
}