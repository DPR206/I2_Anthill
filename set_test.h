/**
 * @brief It declares the tests for the set module
 *
 * @file set_test.h
 * @author Claudia Saiz
 * @version 1
 * @date 28-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test for set_create() initialization
 * @pre None
 * @post set!=NULL
 */
void test1_set_create();

/**
 * @test Test for set_create()
 * @pre None
 * @post All set->ids == NO_ID
 */
void test2_set_create();

/**
 * @test Test for set_create()
 * @pre None
 * @post set->nids == 0
 */
void test3_set_create();

/**
 * @test Test for set_add()
 * @pre Pointer to set = NULL
 * @post output == ERROR
 */
void test1_set_add();

/**
 * @test Test for set_add()
 * @pre id = NO_ID
 * @post output == ERROR
 */
void test2_set_add();

/**
 * @test Test for set_add()
 * @pre Id and set are valid
 * @post output == OK
 */
void test3_set_add();

/**
 * @test Test for set_del()
 * @pre Pointer to set = NULL
 * @post output == ERROR
 */
void test1_set_del();

/**
 * @test Test for set_del()
 * @pre id2 = NO_ID
 * @post output == ERROR
 */
void test2_set_del();

/**
 * @test Test for set_del()
 * @pre id2 not contained in set
 * @post output == ERROR
 */
void test3_set_del();

/**
 * @test Test for set_del()
 * @pre id contained in set
 * @post output == OK
 */
void test4_set_del();

/**
 * @test Test for set_get_id()
 * @pre Pointer to set = NULL
 * @post output == NO_ID
 */
void test1_set_get_id();

/**
 * @test Test for set_get_id()
 * @pre position < 0
 * @post output == NO_ID
 */
void test2_set_get_id();

/**
 * @test Test for set_get_id()
 * @pre set contains supplied Id in position
 * @post output == Supplied Id
 */
void test3_set_get_id();

/**
 * @test Test for set_get_nids()
 * @pre Pointer to set = NULL;
 * @post output == -1
 */
void test1_set_get_nids();

/**
 * @test Test for set_get_nids()
 * @pre Set contains one id
 * @post output == 1
 */
void test2_set_get_nids();

/**
 * @test Test for set_get_position()
 * @pre Pointer to set = NULL
 * @post output == -1
 */
void test1_set_get_position();

/**
 * @test Test for set_get_position()
 * @pre Set contains id
 * @post output == 0
 */
void test2_set_get_position();

/**
 * @test Test for set_contains()
 * @pre Pointer to set = NULL
 * @post output == FALSE
 */
void test1_set_contains();

/**
 * @test Test for set_contains()
 * @pre Id no contained in set
 * @post output == FALSE
 */
void test2_set_contains();

/**
 * @test Test for set_contains()
 * @pre Id contained in set
 * @post output == TRUE
 */
void test3_set_comtains();

#endif