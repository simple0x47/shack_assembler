//
// instruction.h: defines the instruction types, and their limits, compatible with Shack Assembler.
//

#ifndef SHACK_ASSEMBLER_INSTRUCTION_H
#define SHACK_ASSEMBLER_INSTRUCTION_H

#include <stddef.h>

enum instruction_type {
    A_COMMAND,
    C_COMMAND,
    L_COMMAND,
};

typedef enum instruction_type t_instruction_type;

struct instruction {
    t_instruction_type type;
    size_t address;

    char* symbol;
    size_t symbol_length;

    char* destination;
    size_t destination_length;
    char* computation;
    size_t computation_length;
    char* jump;
    size_t jump_length;
};

typedef struct instruction t_instruction;

#endif //SHACK_ASSEMBLER_INSTRUCTION_H
