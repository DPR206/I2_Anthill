/** 
 * @brief It declares the tests for the character module
 * 
 * @file character_test.h
 * @author Duna Puente
 * @version 1 
 * @date 13-03-2025
 * @copyright GNU Public License
 */

#ifndef TEST_CHARACTER_H
#define TEST_CHARACTER_H

/**
 * @test Test function for create character
 * @pre Pointer to character = NON NULL  
 * @post Output==1
 */
void test1_character_create();

/**
 * @test Test function for create character
 * @pre Pointer to character = NON NULL (character_id == NO_ID) 
 * @post Output==NO_ID
 */
void test2_character_create();

/**
 * @test Test function for destroy character
 * @pre Pointer to character = NULL
 * @post Output==ERROR
 */
void test1_character_destroy();

/**
 * @test Test function for destroy character
 * @pre Pointer to character = NON NULL
 * @post Output==OK
 */
void test2_character_destroy();

/**
 * @test Test function for character set id
 * @pre Pointer to character = NULL (id != NO_ID)
 * @post Output==ERROR
 */
void test1_character_setid();

/**
 * @test Test function for character set id
 * @pre Pointer to character = NON NULL (id != NO_ID)
 * @post Output==OK
 */
void test2_character_setid();

/**
 * @test Test function for character get id
 * @pre Pointer to character = NULL
 * @post Output==NO_ID
 */
void test1_character_get_id();

/**
 * @test Test function for character get id
 * @pre Pointer to character = NON NULL (id != NO_ID)
 * @post Output!=NO_ID
 */
void test2_character_get_id();

/**
 * @test Test function for character set name
 * @pre Pointer to character = NULL (pointer to name != NULL)
 * @post Output==ERROR
 */
void test1_character_set_name();

/**
 * @test Test function for character set name
 * @pre Pointer to character = NON NULL (pointer to name != NULL)
 * @post Output==OK
 */
void test2_character_set_name();

/**
 * @test Test function for character get name
 * @pre Pointer to character = NULL 
 * @post Output==NULL
 */
void test1_character_get_name();

/**
 * @test Test function for character get name
 * @pre Pointer to character = NON NULL 
 * @post Output!=NULL
 */
void test2_character_get_name();

/**
 * @test Test function for character set gdesc
 * @pre Pointer to character = NULL (pointer to gdesc != NULL)
 * @post Output==ERROR
 */
void test1_character_set_gdesc();

/**
 * @test Test function for character set gdesc
 * @pre Pointer to character = NON NULL (pointer to gdesc != NULL)
 * @post Output==OK
 */
void test2_character_set_gdesc();

/**
 * @test Test function for character get gdesc
 * @pre Pointer to character = NULL
 * @post Output==NULL
 */
void test1_character_get_gdesc();

/**
 * @test Test function for character get gdesc
 * @pre Pointer to character = NON NULL
 * @post Output!=NULL
 */
void test2_character_get_gdesc();

/**
 * @test Test function for character set health
 * @pre Pointer to character = NULL (health > 0)
 * @post Output==ERROR
 */
void test1_character_set_health();

/**
 * @test Test function for character set health
 * @pre Pointer to character = NON NULL (health > 0)
 * @post Output==OK
 */
void test2_character_set_health();

/**
 * @test Test function for character get health
 * @pre Pointer to character = NULL
 * @post Output==-1
 */
void test1_character_get_health();

/**
 * @test Test function for character get health
 * @pre Pointer to character = NON NULL
 * @post Output=-1
 */
void test2_character_get_health();

/**
 * @test Test function for character set friendly
 * @pre Pointer to character = NULL (friendly == TRUE)
 * @post Output==ERROR
 */
void test1_character_set_friendly();

/**
 * @test Test function for character set friendly
 * @pre Pointer to character = NON NULL (friendly == TRUE)
 * @post Output==OK
 */
void test2_character_set_friendly();

/**
 * @test Test function for character get friendly
 * @pre Friendly == TRUE (pointer to character = NON NULL)
 * @post Output==TRUE
 */
void test1_character_get_friendly();

/**
 * @test Test function for character get friendly
 * @pre Friendly == FALSE (pointer to character = NON NULL)
 * @post Output==FALSE
 */
void test2_character_get_friendly();

/**
 * @test Test function for character set message
 * @pre Pointer to character = NULL (message != NULL)
 * @post Output==ERROR
 */
void test1_character_set_message();

/**
 * @test Test function for character set message
 * @pre Pointer to character = NON NULL (message != NULL)
 * @post Output==OK
 */
void test2_character_set_message();

/**
 * @test Test function for character get message
 * @pre Pointer to character = NULL
 * @post Output==NULL
 */
void test1_character_get_message();

/**
 * @test Test function for character get message
 * @pre Pointer to character = NON NULL
 * @post Output!=NULL
 */
void test2_character_get_message();

#endif