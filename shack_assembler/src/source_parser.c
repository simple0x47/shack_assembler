//
// source_parser.c: reads the input files and retrieves the hack assembly instructions from it.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "source_parser.h"
#include "instruction.h"

#define ASSIGNMENT_INSTRUCTION '='
#define JUMP_SEPARATOR ';'
#define SUM_INSTRUCTION '+'
#define SUBTRACTION_INSTRUCTION '-'
#define AND_BITWISE_INSTRUCTION '&'
#define OR_BITWISE_INSTRUCTION '|'

#define AT_OPERATOR '@'
#define JUMP_OPERATOR_START '('
#define JUMP_OPERATOR_END ')'

int contains_line_any_code(const char* line, size_t line_count);
char* format_code_line(const char* line, size_t line_count);
t_instruction* retrieve_instruction_from_formatted_line(const char* formatted_line, size_t line_count);

int read_source_file(int verbose_mode, const char* file_path, t_array_list* commands_buffer) {
    if (file_path == NULL) {
        printf("Internal Error: 'file_path' is NULL at 'read_source_file'.\n");
        return -1;
    }

    if (commands_buffer == NULL) {
        printf("Internal Error: 'commands_buffer' is NULL at 'read_source_file'.\n");
        return -1;
    }

    if (commands_buffer->type != LIST) {
        printf("Internal Error: 'commands_buffer' is not a list at 'read_source_file'.\n");
        return -1;
    }

    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Internal Error: failed to open file '%s'.\n", file_path);
        return -1;
    }

    const int MAX_CHARACTERS_PER_LINE = 256;

    char* line = malloc(sizeof(char) * MAX_CHARACTERS_PER_LINE);

    if (line == NULL) {
        fclose(file);
        printf("Internal Error: failed to allocate memory for 'line' at 'read_source_file.\n");
        return -1;
    }

    size_t line_count = 0;
    while (fgets(line, MAX_CHARACTERS_PER_LINE, file)) {
        int result = contains_line_any_code(line, line_count);

        if (result > 0) {
            char* formatted_line = format_code_line(line, line_count);

            if (formatted_line == NULL) {
                free(line);
                fclose(file);
                return -1;
            }

            if (verbose_mode) {
                printf("Analyzing instruction: %s\n", formatted_line);
            }

            t_instruction* instruction = retrieve_instruction_from_formatted_line(formatted_line, line_count);

            if (instruction == NULL) {
                free(formatted_line);
                free(line);
                fclose(file);
                printf("Internal Error: failed to retrieve instruction from formatted line at 'read_source_file'.\n");
                return -1;
            }

            result = add_item_to_array_list(commands_buffer, instruction);

            if (result < 0) {
                free(instruction);
                free(formatted_line);
                free(line);
                fclose(file);
                printf("Internal Error: failed to store instruction at 'read_source_file'.\n");
                return -1;
            }

            if (verbose_mode) {
                printf("Successfully stored instruction: %s\n", formatted_line);
            }

            free(formatted_line);

            if (instruction->type != L_COMMAND) {
                line_count++;
            }
        }
        else if (result < 0) {
            free(line);
            fclose(file);
            return -1;
        }
    }

    free(line);
    fclose(file);

    return 1;
}

int is_character_legal(char character) {
    if (isalnum(character)) {
        return 1;
    }

    switch (character) {
        case ASSIGNMENT_INSTRUCTION:
        case JUMP_SEPARATOR:
        case SUM_INSTRUCTION:
        case SUBTRACTION_INSTRUCTION:
        case AND_BITWISE_INSTRUCTION:
        case OR_BITWISE_INSTRUCTION:
        case AT_OPERATOR:
        case JUMP_OPERATOR_START:
        case JUMP_OPERATOR_END:
        case '_':
        case '.':
        case '$':
        case ':':
            return 1;
        default:
            return 0;
    }
}

int contains_line_any_code(const char* line, size_t line_count) {
    if (line == NULL) {
        printf("Internal Error: 'line' is null at 'contains_line_any_code'.\n");
        return -1;
    }

    const size_t line_length = strlen(line);

    if (line_length == 0L) {
        return 0;
    }

    for (size_t i = 0; i < line_length; i++) {
        char character = line[i];

        if (!isspace(character)) {
            if (character == '/') {
                if ((i + 1) < line_length) {
                    if (line[i + 1] == '/') {
                        break;
                    }
                    else {
                        printf("Error: invalid '/' symbol detected at line '%lu'.\n", line_count);
                        return -1;
                    }
                }
            }
            else if (is_character_legal(character)) {
                return 1;
            }
            else {
                printf("Error: invalid '%c' symbol detected at line '%lu'.\n", character, line_count);
                return -1;
            }
        }
    }

    return 0;
}

char* format_code_line(const char* line, size_t line_count) {
    if (line == NULL) {
        printf("Internal Error: 'line' is null at 'format_code_line'.\n");
        return NULL;
    }

    const size_t line_length = strlen(line);

    if (line_length == 0L) {
        printf("Internal Error: 'line' is empty.\n");
        return NULL;
    }

    size_t formatted_line_length = 0L;
    for (size_t i = 0; i < line_length; i++) {
        char character = line[i];

        if (!isspace(character)) {
            if (character == '/') {
                if ((i + 1) < line_length) {
                    if (line[i + 1] == '/') {
                        break;
                    }
                    else {
                        printf("Error: invalid '/' symbol detected at line '%lu'.\n", line_count);
                        return NULL;
                    }
                }
            }
            else if (is_character_legal(character)) {
                formatted_line_length++;
            }
            else {
                printf("Error: invalid '%c' symbol detected at line '%lu'.\n", character, line_count);
                return NULL;
            }
        }
    }

    char* formatted_line = malloc(sizeof(char) * (formatted_line_length + 1));

    if (formatted_line == NULL) {
        printf("Internal Error: failed to allocate memory for 'formatted_line' at 'format_code_line'.\n");
        return NULL;
    }

    for (size_t i = 0, formatted_line_index = 0; (i < line_length) && (formatted_line_index < formatted_line_length); i++) {
        char character = line[i];

        if (!isspace(character)) {
            if (character == '/') {
                if ((i + 1) < line_length) {
                    if (line[i + 1] == '/') {
                        break;
                    }
                    else {
                        printf("Error: invalid '/' symbol detected at line '%lu'.\n", line_count);
                        return NULL;
                    }
                }
            }
            else if (is_character_legal(character)) {
                formatted_line[formatted_line_index] = character;
                formatted_line_index++;
            }
            else {
                printf("Error: invalid '%c' symbol detected at line '%lu'.\n", character, line_count);
                return NULL;
            }
        }
    }

    formatted_line[formatted_line_length] = '\0';

    return formatted_line;
}

t_instruction* retrieve_instruction_from_formatted_line(const char* formatted_line, size_t line_count) {
    if (formatted_line == NULL) {
        printf("Internal Error: 'formatted_line' is NULL at 'retrieve_instruction_from_formatted_line'.\n");
        return NULL;
    }

    if (strlen(formatted_line) == 0L) {
        printf("Internal Error: 'formatted_line' is empty at 'retrieve_instruction_from_formatted_line'.\n");
        return NULL;
    }

    t_instruction* instruction = malloc(sizeof(t_instruction));

    if (instruction == NULL) {
        printf("Internal Error: failed to allocate memory for 'instruction' at 'retrieve_instruction_from_formatted_line'.\n");
        return NULL;
    }

    t_instruction_type type;

    if (formatted_line[0] == AT_OPERATOR) {
        type = A_COMMAND;
    }
    else if (formatted_line[0] == JUMP_OPERATOR_START) {
        type = L_COMMAND;
    }
    else {
        type = C_COMMAND;
    }

    instruction->type = type;

    if ((type == A_COMMAND) || (type == L_COMMAND)) {
        size_t operators_count = (type == A_COMMAND) ? 1 : 2;

        size_t symbol_length = strlen(formatted_line) - operators_count;
        char* symbol = malloc(sizeof(char) * (symbol_length + 1)); // +1, in order to add '\0' at the end.

        if (symbol == NULL) {
            free(instruction);
            printf("Internal Error: failed to allocate memory for 'symbol' at 'retrieve_instruction_from_formatted_line'.\n");
            return NULL;
        }

        for (size_t i = 0; i < symbol_length; i++) {
            symbol[i] = formatted_line[i + 1]; // i + 1, in order to skip the operator at the start of the line.
        }

        symbol[symbol_length] = '\0';

        instruction->symbol = symbol;
        instruction->symbol_length = symbol_length;

        instruction->destination = NULL;
        instruction->destination_length = 0L;

        instruction->jump = NULL;
        instruction->jump_length = 0L;

        instruction->computation = NULL;
        instruction->computation_length = 0L;
    }
    else {
        instruction->symbol = NULL;
        instruction->symbol_length = 0L;

        if (strchr(formatted_line, ASSIGNMENT_INSTRUCTION) != NULL) {
            size_t destination_length = (strchr(formatted_line, ASSIGNMENT_INSTRUCTION) - formatted_line);
            char* destination = malloc(sizeof(char) * (destination_length + 1)); // +1, in order to add '\0' at the end.

            if (destination == NULL) {
                free(instruction);
                printf("Internal Error: failed to allocate memory for 'destination' at 'retrieve_instruction_from_formatted_line'.\n");
                return NULL;
            }

            memccpy(destination, formatted_line, ASSIGNMENT_INSTRUCTION, sizeof(char) * destination_length);
            destination[destination_length] = '\0';

            instruction->destination = destination;
            instruction->destination_length = destination_length;
        }
        else {
            instruction->destination = NULL;
            instruction->destination_length = 0L;
        }

        if (strchr(formatted_line, JUMP_SEPARATOR) != NULL) {
            size_t jump_separator_position = (strchr(formatted_line, JUMP_SEPARATOR) - formatted_line);
            size_t jump_length = strlen(formatted_line) - (jump_separator_position + 1);
            char* jump = malloc(sizeof(char) * (jump_length + 1)); // +1, in order to add '\0' at the end.

            if (jump == NULL) {
                if (instruction->destination != NULL) {
                    free(instruction->destination);
                }

                free(instruction);
                printf("Internal Error: failed to allocate memory for 'jump' at 'retrieve_instruction_from_formatted_line'.\n");
                return NULL;
            }

            for (size_t i = 0; i < jump_length; i++) {
                jump[i] = formatted_line[jump_separator_position + i + 1]; // + 1, in order to skip the jump separator.
            }

            jump[jump_length] = '\0';

            instruction->jump = jump;
            instruction->jump_length = jump_length;
        }
        else {
            instruction->jump = NULL;
            instruction->jump_length = 0L;
        }

        size_t start_computation = (instruction->destination == NULL) ? 0L : (instruction->destination_length + 1);
        size_t end_computation = (instruction->jump == NULL) ? (strlen(formatted_line) - 1) :
                                 ((strlen(formatted_line) - (instruction->jump_length + 1)) - 1);

        size_t computation_length = (end_computation - start_computation) + 1; // + 1, array positioning to characters count.
        char* computation = malloc(sizeof(char) * (computation_length + 1)); // +1, in order to add '\0' at the end.

        if (computation == NULL) {
            if (instruction->destination != NULL) {
                free(instruction->destination);
            }

            if (instruction->jump != NULL) {
                free(instruction->jump);
            }

            free(instruction);
            printf("Internal Error: failed to allocate memory for 'computation' at 'retrieve_instruction_from_formatted_line'.\n");
            return NULL;
        }

        for (size_t i = 0; i < computation_length; i++) {
            computation[i] = formatted_line[start_computation + i];
        }

        computation[computation_length] = '\0';

        instruction->computation = computation;
        instruction->computation_length = computation_length;
    }

    instruction->address = (type == A_COMMAND) ? 0L : line_count;

    return instruction;
}

int dispose_commands_from_buffer(t_array_list* commands_buffer) {
    if (commands_buffer == NULL) {
        printf("Internal Error: 'commands_buffer' is null at 'dispose_commands_from_buffer'.\n");
        return -1;
    }

    if (commands_buffer->type != LIST) {
        printf("Internal Error: 'commands_buffer' is not a list at 'dispose_commands_from_buffer'.\n");
        return -1;
    }

    for (size_t i = 0; i < commands_buffer->length; i++) {
        t_instruction* instruction = commands_buffer->item[i];

        if (instruction == NULL) {
            printf("Internal Error: 'commands_buffer' contains invalid data at 'dispose_commands_from_buffer'.\n");
            return -1;
        }

        if ((instruction->type == A_COMMAND) || (instruction->type == L_COMMAND)) {
            if (instruction->symbol == NULL) {
                printf("Internal Error: 'commands_buffer' contains invalid data at 'dispose_commands_from_buffer'.\n");
                return -1;
            }

            free(instruction->symbol);
        }
        else if (instruction->type == C_COMMAND) {
            if (instruction->computation == NULL) {
                printf("Internal Error: 'commands_buffer' contains invalid data at 'dispose_commands_from_buffer'.\n");
                return -1;
            }

            free(instruction->computation);

            if (instruction->destination != NULL) {
                free(instruction->destination);
            }

            if (instruction->jump != NULL) {
                free(instruction->jump);
            }
        }
        else {
            printf("Internal Error: 'commands_buffer' contains invalid data at 'dispose_commands_from_buffer'.\n");
            return -1;
        }

        free(instruction);
    }

    return 1;
}