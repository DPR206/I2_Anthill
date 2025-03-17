/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Claudia Saiz
 * @version 2.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre Pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre Pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space_north setting
 * @pre Pointer to space = NON NULL (north_id != NO ID)
 * @post Output==OK
 */
void test1_space_set_north();

/**
 * @test Test function for space_north setting
 * @pre Pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_north();

/**
 * @test Test function for space_south setting
 * @pre Pointer to space = NON NULL (south_id != NO ID)
 * @post Output==OK
 */
void test1_space_set_south();

/**
 * @test Test function for space_south setting
 * @pre Pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_south();

/**
 * @test Test function for space_east setting
 * @pre Pointer to space = NON NULL (east_id != NO ID)
 * @post Output==OK
 */
void test1_space_set_east();

/**
 * @test Test function for space_east setting
 * @pre Pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_east();

/**
 * @test Test function for space_west setting
 * @pre Pointer to space = NON NULL (west_id != NO ID)
 * @post Output==OK
 */
void test1_space_set_west();

/**
 * @test Test function for space_west setting
 * @pre Pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_west();

/**
 * @test Test function for space_object setting
 * @pre Pointer to space = NON NULL (object_id != NO ID)
 * @post Output==OK
 */
void test1_space_set_object();

/**
 * @test Test function for space_object setting
 * @pre Pointer to space = NULL (object_id != NO ID)
 * @post Output==ERROR
 */
void test2_space_set_object();

/**
 * @test Test function for space_object setting
 * @pre Object id = NULL (pointer to space = NON NULL)
 * @post Output==ERROR
 */
void test3_space_set_object();

/**
 * @test Test function for getting space_id
 * @pre Pointer to space = NON NULL (space_id != NO_ID)
 * @post Output!=NO_ID
 */
void test1_space_get_id();

/**
 * @test Test function for getting space_id
 * @pre Pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_id();

/**
 * @test Test function for getting space_name
 * @pre Pointer to space name == NON NULL (pointer to space = NON NULL)
 * @post Output==0
 */
void test1_space_get_name();

/**
 * @test Test function for getting space_name
 * @pre Pointer to space = NON NULL
 * @post Output==NULL
 */
void test2_space_get_name();

/**
 * @test Test function for getting space_north_id
 * @pre North_id != NO_ID (pointer to space = NON NULL)
 * @post Output!=NO_ID
 */
void test1_space_get_north();

/**
 * @test Test function for getting space_north_id
 * @pre Pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_north();

/**
 * @test Test function for getting space_south_id
 * @pre South_id != NO_ID (pointer to space = NON NULL)
 * @post Output!=NO_ID
 */
void test1_space_get_south();

/**
 * @test Test function for getting space_south_id
 * @pre Pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_south();

/**
 * @test Test function for getting space_east_id
 * @pre East_id != NO_ID (pointer to space = NON NULL)
 * @post Output!=NO_ID
 */
void test1_space_get_east();

/**
 * @test Test function for getting space_east_id
 * @pre Pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_east();

/**
 * @test Test function for getting space_west_id
 * @pre West_id != NO_ID (pointer to space = NON NULL)
 * @post Output!=NO_ID
 */
void test1_space_get_west();

/**
 * @test Test function for getting space_west_id
 * @pre Pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_west();

/**
 * @test Test function for getting space_objects
 * @pre Pointer to space = NON NULL (objects_id = NO_ID )
 * @post Output!=NULL
 */
void test1_space_get_objects();

/**
 * @test Test function for getting space_objects
 * @pre Pointer to space = NON NULL (objects_id != NO_ID )
 * @post Output!=NULL
 */
void test2_space_get_objects();

/**
 * @test Test function for getting space_objects
 * @pre Pointer to space = NULL
 * @post Output==NULL
 */
void test3_space_get_objects();

/**
 * @test Test function for adding space_objects
 * @pre Pointer to space = NULL (object_id != NO_ID )
 * @post Output==ERROR
 */
void test1_space_add_object();

/**
 * @test Test function for adding space_objects
 * @pre Object_id = NO_ID (pointer to space = NON NULL)
 * @post Output==ERROR
 */
void test2_space_add_object();

/**
 * @test Test function for adding space_objects
 * @pre Object_id != NO_ID (pointer to space = NON NULL)
 * @post Output==OK
 */
void test3_space_add_object();

/**
 * @test Test function for getting space_objects_id
 * @pre Pointer to space = NULL (position > 0)
 * @post Output==NO_ID
 */
void test1_space_get_objects_id();

/**
 * @test Test function for getting space_objects_id
 * @pre Position < 0 (pointer to space = NON NULL) 
 * @post Output==NO_ID
 */
void test2_space_get_objects_id();

/**
 * @test Test function for getting space_objects_id
 * @pre Position > 0 (pointer to space = NON NULL) 
 * @post Output!=NO_ID
 */
void test3_space_get_objects_id();

/**
 * @test Test function for getting if an object is a space 
 * @pre Pointer to space = NULL (object_id != NO_ID)
 * @post Output==FALSE
 */
void test1_space_at_object();

/**
 * @test Test function for getting if an object is a space 
 * @pre Object_id != object_id in the space (pointer to space = NON NULL)
 * @post Output==FALSE
 */
void test2_space_at_object();

/**
 * @test Test function for getting if an object is a space 
 * @pre Object_id == object_id in the space (pointer to space = NON NULL)
 * @post Output==TRUE
 */
void test3_space_at_object();

/**
 * @test Test function for setting space_character
 * @pre Pointer to space = NULL (character != NULL)
 * @post Output==ERROR
 */
void test1_space_set_character();

/**
 * @test Test function for setting space_character
 * @pre Pointer to space = NON NULL (character != NULL)
 * @post Output==OK
 */
void test2_space_set_character();

/**
 * @test Test function for getting space_character
 * @pre Pointer to space = NULL
 * @post Output==NULL
 */
void test1_space_get_character();

/**
 * @test Test function for getting space_character
 * @pre Pointer to space = NON NULL
 * @post Output!=NULL
 */
void test2_space_get_character();

/**
 * @test Test function for setting space_gdesc
 * @pre Pointer to space = NULL (gdesc != NULL)
 * @post Output==ERROR
 */
void test1_space_set_gdesc();

/**
 * @test Test function for setting space_gdesc
 * @pre Pointer to space = NON NULL (gdesc != NULL)
 * @post Output==OK
 */
void test2_space_set_gdesc();

/**
 * @test Test function for setting space_gdesc
 * @pre Pointer to space = NULL
 * @post Output==NULL
 */
void test1_space_get_gdesc();

/**
 * @test Test function for setting space_gdesc
 * @pre Pointer to space == NON NULL
 * @post Output!=NULL
 */
void test2_space_get_gdesc();

#endif