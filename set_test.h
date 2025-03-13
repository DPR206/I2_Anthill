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
 * @test Test set creation
 * @pre 
 * @post Set is not NULL
 */
void test1_set_create();

/**
 * @test Test set creation
 * @pre 
 * @post All set->ids == NO_ID
 */
void test2_set_create();

/**
 * @test Test set creation
 * @pre  
 * @post set->nids == 0
 */
void test3_set_create();
void test1_set_add();
void test2_set_add();
void test3_set_add();
void test1_set_del();
void test2_set_del();
void test3_set_del();
void test4_set_del();
void test1_set_get_id();
void test2_set_get_id();
void test3_set_get_id();
void test1_set_get_nids();
void test2_set_get_nids();
void test1_set_get_position();
void test2_set_get_position();

#endif