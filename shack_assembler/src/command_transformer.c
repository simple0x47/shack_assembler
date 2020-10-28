//
// command_transformer.c: converts the retrieved commands into an array of integers.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command_transformer.h"
#include "instruction.h"

#define C_INSTRUCTION_HEADER 0b1110000000000000
#define MEMORY_INSTRUCTION_MODE 0b0001000000000000

/* MNEMONICS */

#define MEMORY 'M'
#define A_REGISTER 'A'
#define D_REGISTER 'D'

#define JUMP_GREATER_THAN_ZERO "JGT"
#define JUMP_EQUAL_TO_ZERO "JEQ"
#define JUMP_GREATER_OR_EQUAL_TO_ZERO "JGE"
#define JUMP_LOWER_THAN_ZERO "JLT"
#define JUMP_NOT_EQUAL_TO_ZERO "JNE"
#define JUMP_LOWER_OR_EQUAL_TO_ZERO "JLE"
#define JUMP "JMP"

/* COMPUTATION INSTRUCTIONS */
#define ZERO 0b101010000000
#define ONE 0b111111000000
#define NEGATIVE_ONE 0b111010000000
#define D_REGISTER_VALUE 0b001100000000
#define A_REGISTER_VALUE 0b110000000000
#define NOT_BITWISE_D_REGISTER 0b001101000000
#define NOT_BITWISE_A_REGISTER 0b110001000000
#define NEGATIVE_D_REGISTER 0b001111000000
#define NEGATIVE_A_REGISTER 0b110001000000
#define INCREMENT_D_REGISTER 0b011111000000
#define INCREMENT_A_REGISTER 0b110111000000
#define DECREASE_D_REGISTER 0b001110000000
#define DECREASE_A_REGISTER 0b110010000000
#define SUM_D_REGISTER_AND_A_REGISTER 0b000010000000
#define SUB_D_REGISTER_AND_A_REGISTER 0b010011000000
#define SUB_A_REGISTER_AND_D_REGISTER 0b000111000000
#define BITWISE_AND_D_REGISTER_AND_A_REGISTER 0b000000000000
#define BITWISE_OR_D_REGISTER_AND_A_REGISTER 0b010101000000

/* DESTINATION INSTRUCTIONS */

#define MEMORY_DESTINATION 0b001
#define D_REGISTER_DESTINATION 0b010
#define A_REGISTER_DESTINATION 0b100

/* JUMP INSTRUCTIONS */

#define GREATER_THAN_ZERO 0b001
#define EQUAL_TO_ZERO 0b010
#define LOWER_THAN_ZERO 0b100

size_t get_number_from_string(const char* string);
size_t power(size_t base, size_t power);

unsigned int* translate_instructions_into_binary(const t_array_list* commands_buffer) {
    if (commands_buffer == NULL) {
        printf("Internal Error: null 'commands_buffer' at 'translate_instructions_into_binary'.\n");
        return NULL;
    }

    int instruction_count = 0;

    for (int i = 0; i < commands_buffer->length; i++) {
        t_instruction* command = commands_buffer->item[i];

        if (command == NULL) {
            printf("Internal Error: null 'command' at 'translate_instructions_into_binary'.\n");
            return NULL;
        }

        if ((command->type == A_COMMAND) || (command->type == C_COMMAND)) {
            instruction_count++;
        }
    }

    unsigned int* buffer = malloc(sizeof(unsigned int) * (instruction_count + 1));

    if (buffer == NULL) {
        printf("Internal Error: could not allocate memory for 'buffer' at 'translate_instructions_into_binary'.\n");
        return NULL;
    }

    for (unsigned int i = 0, j = 0; (i < commands_buffer->length) && (j < instruction_count); i++) {
        t_instruction* command = commands_buffer->item[i];

        if (command == NULL) {
            printf("Internal Error: null 'command' at 'translate_instructions_into_binary'.\n");
            return NULL;
        }

        size_t instruction;

        if (command->type == C_COMMAND) {
            instruction = C_INSTRUCTION_HEADER;

            if (command->computation == NULL) {
                printf("Internal Error: 'commands_buffer' contains invalid data at 'translate_instructions_into_binary'.\n");
                return NULL;
            }

            char* computation = command->computation;
            if (strchr(computation, MEMORY) != NULL) {
                instruction += MEMORY_INSTRUCTION_MODE;
            }

            if (strcmp(computation, "0") == 0) {
                instruction += ZERO;
            }
            else if (strcmp(computation, "1") == 0) {
                instruction += ONE;
            }
            else if (strcmp(computation, "-1") == 0) {
                instruction += NEGATIVE_ONE;
            }
            else if (strcmp(computation, "D") == 0) {
                instruction += D_REGISTER_VALUE;
            }
            else if ((strcmp(computation, "A") == 0) || (strcmp(computation, "M") == 0)) {
                instruction += A_REGISTER_VALUE;
            }
            else if (strcmp(computation, "!D" ) == 0) {
                instruction += NOT_BITWISE_D_REGISTER;
            }
            else if ((strcmp(computation, "!A") == 0) || (strcmp(computation, "!M") == 0)) {
                instruction = instruction + NOT_BITWISE_A_REGISTER; // clang tidy, freaks out if += in here...
            }
            else if (strcmp(computation, "-D") == 0) {
                instruction += NEGATIVE_D_REGISTER;
            }
            else if ((strcmp(computation, "-A") == 0) || (strcmp(computation, "-M") == 0)) {
                instruction += NEGATIVE_A_REGISTER;
            }
            else if (strcmp(computation, "D+1") == 0) {
                instruction += INCREMENT_D_REGISTER;
            }
            else if ((strcmp(computation, "A+1") == 0) || (strcmp(computation, "M+1") == 0)) {
                instruction += INCREMENT_A_REGISTER;
            }
            else if (strcmp(computation, "D-1") == 0) {
                instruction += DECREASE_D_REGISTER;
            }
            else if ((strcmp(computation, "A-1") == 0) || (strcmp(computation, "M-1") == 0)) {
                instruction += DECREASE_A_REGISTER;
            }
            else if ((strcmp(computation, "D+A") == 0) || (strcmp(computation, "A+D") == 0) ||
                     (strcmp(computation, "D+M") == 0) || (strcmp(computation, "M+D") == 0)) {
                instruction += SUM_D_REGISTER_AND_A_REGISTER;
            }
            else if ((strcmp(computation, "D-A") == 0) || (strcmp(computation, "D-M") == 0)) {
                instruction += SUB_D_REGISTER_AND_A_REGISTER;
            }
            else if ((strcmp(computation, "A-D") == 0) || (strcmp(computation, "M-D") == 0)) {
                instruction += SUB_A_REGISTER_AND_D_REGISTER;
            }
            else if ((strcmp(computation, "D&A") == 0) || (strcmp(computation, "D&M") == 0)) {
                instruction += BITWISE_AND_D_REGISTER_AND_A_REGISTER;
            }
            else if ((strcmp(computation, "D|A") == 0) || (strcmp(computation, "D|M") == 0)) {
                instruction += BITWISE_OR_D_REGISTER_AND_A_REGISTER;
            }
            else {
                printf("Error: unknown computation command '%s'.\n", computation);
                return NULL;
            }

            if (command->destination != NULL) {
                char* destination = command->destination;

                if (strchr(destination, MEMORY) != NULL) {
                    instruction += MEMORY_DESTINATION;
                }

                if (strchr(destination, A_REGISTER) != NULL) {
                    instruction += A_REGISTER_DESTINATION;
                }

                if (strchr(destination, D_REGISTER) != NULL) {
                    instruction += D_REGISTER_DESTINATION;
                }
            }

            if (command->jump != NULL) {
                char* jump = command->jump;

                if (strcmp(jump, JUMP_EQUAL_TO_ZERO) == 0) {
                    instruction += EQUAL_TO_ZERO;
                }
                else if (strcmp(jump, JUMP_GREATER_THAN_ZERO) == 0) {
                    instruction += GREATER_THAN_ZERO;
                }
                else if (strcmp(jump, JUMP_GREATER_OR_EQUAL_TO_ZERO) == 0) {
                    instruction += EQUAL_TO_ZERO + GREATER_THAN_ZERO;
                }
                else if (strcmp(jump, JUMP_LOWER_THAN_ZERO) == 0) {
                    instruction += LOWER_THAN_ZERO;
                }
                else if (strcmp(jump, JUMP_LOWER_OR_EQUAL_TO_ZERO) == 0) {
                    instruction += EQUAL_TO_ZERO + LOWER_THAN_ZERO;
                }
                else if (strcmp(jump, JUMP_NOT_EQUAL_TO_ZERO) == 0) {
                    instruction += LOWER_THAN_ZERO + GREATER_THAN_ZERO;
                }
                else if (strcmp(jump, JUMP) == 0) {
                    instruction += EQUAL_TO_ZERO + GREATER_THAN_ZERO + LOWER_THAN_ZERO;
                }
                else {
                    printf("Error: invalid jump mnemonic '%s'.\n", jump);
                    return NULL;
                }
            }

            buffer[j] = instruction;
            j++;
        }
        else if (command->type == A_COMMAND) {
            if (isdigit(*(command->symbol))) {
                instruction = get_number_from_string(command->symbol);
            }
            else {
                instruction = command->address;
            }

            buffer[j] = instruction;
            j++;
        }
    }

    buffer[instruction_count] = -1;

    return buffer;
}

size_t get_number_from_string(const char* string) {
    size_t number = 0;
    size_t string_size = strlen(string);
    for (size_t i = 0; i < string_size; i++) {
        number += ((string[i] - '0') * power(10, string_size - i));
    }

    return number;
}

size_t power(size_t base, size_t power) {
    size_t result = 1;

    for (size_t i = 0; i < power; i++) {
        result *= base;
    }

    return result;
}