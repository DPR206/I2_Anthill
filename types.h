/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

/**
 * @brief This represents an identifier for any element in the game
 * 
 */
typedef long Id;

/**
 * @brief This represents boolean values, true or false
 * 
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief This represents the status of an operation, whether it was successful or not
 * 
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Represents possible directions in the game (North, South, East, West)
 * 
 */
typedef enum { N, S, E, W } Direction;

#endif
