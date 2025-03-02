/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Claudia Saiz
 * @version 1
 * @date 28-02-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include "set.h"
 #include "set_test.h"
 #include "test.h"

 #define MAX_TESTS 40

/** 
 * @brief Main function for SET unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test3_set_create();
  if (all || test == 4) test1_set_add();
  if (all || test == 5) test2_set_add();
  if (all || test == 6) test3_set_add();
  if (all || test == 7) test1_set_del();
  if (all || test == 8) test2_set_del();
  if (all || test == 9) test3_set_del();
  if (all || test == 10) test4_set_del();
  if (all || test == 11) test1_set_get_id();
  if (all || test == 12) test2_set_get_id();
  if (all || test == 13) test3_set_get_id();
  if (all || test == 14) test1_set_get_nids();
  if (all || test == 15) test2_set_get_nids();
  if (all || test == 16) test1_set_get_position();
  if (all || test == 17) test2_set_get_position();
 


  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_set_create(){
  int result;
  Set *set=NULL;
  set = set_create();
  result=set!=NULL ;
  PRINT_TEST_RESULT(result);
  set_destroy(set);
}

void test2_set_create(){
  Set *set=NULL;
  int position=5;
  set = set_create();
  PRINT_TEST_RESULT(set_get_id(set, position) == NO_ID);
  set_destroy(set);
}

void test3_set_create(){
  Set *set=NULL;
  set = set_create();
  PRINT_TEST_RESULT(set_get_nids(set) == 0);
  set_destroy(set);
}

void test1_set_add(){
  Set *set=NULL;
  Id id=5;
  PRINT_TEST_RESULT(set_add(set, id)==ERROR);
}

void test2_set_add(){
  Set *set=NULL;
  Id id=NO_ID;
  set = set_create();
  PRINT_TEST_RESULT(set_add(set, id)==ERROR);
  set_destroy(set);
}

void test3_set_add(){
  Set *set=NULL;
  Id id=5;
  set = set_create();
  PRINT_TEST_RESULT(set_add(set, id)==OK);
  set_destroy(set);
}

void test1_set_del(){
  Set *set=NULL;
  Id id=5;
  PRINT_TEST_RESULT(set_del(set, id)==ERROR);
  set_destroy(set);
}

void test2_set_del(){
  Set *set=NULL;
  Id id1=5, id2=NO_ID;
  set=set_create();
  set_add(set, id1);
  PRINT_TEST_RESULT(set_del(set, id2)==ERROR);
  set_destroy(set);
}

void test3_set_del(){
  Set *set=NULL;
  Id id1=5, id2=10;
  set=set_create();
  set_add(set, id1);
  PRINT_TEST_RESULT(set_del(set, id2)==ERROR);
  set_destroy(set);
}

void test4_set_del(){
  Set *set=NULL;
  Id id=5;
  set=set_create();
  set_add(set, id);
  PRINT_TEST_RESULT(set_del(set, id)==OK);
  set_destroy(set);
}

void test1_set_get_id(){
  Set *set=NULL;
  int position=0;
  PRINT_TEST_RESULT(set_get_id(set, position)==NO_ID);
}

void test2_set_get_id(){
  Set *set=NULL;
  int position=-1;
  set=set_create();
  PRINT_TEST_RESULT(set_get_id(set, position)==NO_ID);
  set_destroy(set);
}

void test3_set_get_id(){
  Set *set=NULL;
  Id id=5;
  int position=0;
  set=set_create();
  set_add(set, id);
  PRINT_TEST_RESULT(set_get_id(set, position)==id);
  set_destroy(set);
}

void test1_set_get_nids(){
  Set *set=NULL;
  PRINT_TEST_RESULT(set_get_nids(set)==-1);
}

void test2_set_get_nids(){
  Set *set=NULL;
  Id id=5;
  set=set_create;
  set_add(set, id);
  PRINT_TEST_RESULT(set_get_nids(set)==1);
  set_destroy(set);
}

void test1_set_get_position(){
  Set *set=NULL;
  Id id=5;
  PRINT_TEST_RESULT(set_get_position(set, id)==-1);
}

void test2_set_get_position(){
  Set *set=NULL;
  Id id=5;
  set=set_create();
  set_add(set, id);
  PRINT_TEST_RESULT(set_get_position(set, id)==0);
  set_destroy(set);
}