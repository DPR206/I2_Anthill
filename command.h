/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 2
 * @date 04-03-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 11

/**
 * @brief Types of commands:
 * - CMDS: string representation of the command
 * - CMDL: alternative representation of the command
 *
 */
typedef enum {CMDS, CMDL} CommandType;

/**
 * @brief Possible command codes:
 * - NO_CMD: no command
 * - UNKNOWN: unknown command
 * - EXIT: exit command
 * - NEXT: next command
 * - BACK: back command
 * - TAKE: take an object from the space command
 * - DROP: drop the object it is carrying in the space
 * - LEFT: left command
 * - RIGHT: right command
 * - ATTACK: attack a character who isn't a friend in the space
 */
typedef enum {NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, TAKE, DROP, LEFT, RIGHT, ATTACK, CHAT} CommandCode;

/**
 * @brief This struct holds the information of a command, the code that represents the command type
 *
 */
typedef struct _Command Command;

/**
 * @brief It allocates memory for a new command and initializes it
 * @author Profesores PPROG
 *
 * @return Command* Pointer to the created commando or NULL if memory allocation fails
 */
Command *command_create();

/**
 * @brief It frees the memory used by a command and sets the pointer to NULL
 * @author Profesores PPROG
 *
 * @param command Pointer to the command to destroy
 * @return Status, OK if succesful or ERROR if the pointer to the command is NULL
 */
Status command_destroy(Command *command);

/**
 * @brief It assigns a command code to a provided command
 * @author Profesores PPROG
 *
 * @param command Pointer to the command
 * @param code The  command code to set
 * @return Status, OK if succesful or ERROR if the pointer to the command is NULL
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief It returns a commandcode from a command
 * @author Profesores PPROG
 *
 * @param command Pointer to the command
 * @return CommandCode, the command code stored in the command, or NO_CMD if the command is NULL
 */
CommandCode command_get_code(Command *command);

/**
 * @brief It sets the string of the command
 * @author Duna Puente
 * 
 * @param command Pointer to the command
 * @param string Pointer to the string
 * @return Status, OK if  successful, or ERROR if there was a problem with the command. 
 */
Status command_set_string(Command *command, char *string);

/**
 * @brief It gets the string of a command
 * @author Duna Puente
 * 
 * @param command Pointer to the command
 * @return Pointer to the string of the command
 */
char *command_get_string(Command *command);

/**
 * @brief Reads a line of input from the user, and sets the command code to a provided command
 * @author Profesores PPROG
 *
 * @param command Pointer to the command that will hold the code
 * @return Status, OK if  successful, or ERROR if there was a problem with the command.
 */
Status command_get_user_input(Command *command);

#endif
