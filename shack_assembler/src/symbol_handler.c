//
// symbol_handler.c: detects symbols within a commands buffer, and proceeds to sync A_COMMANDS, references to labels,
// addresses to the referenced label ones (L_COMMAND).
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symbol_handler.h"
#include "instruction.h"

#define RAM_SYMBOL_MAX_CHARACTERS 4
#define RAM_SYMBOLS_COUNT 16
#define VARIABLE_START_ADDRESS 16

/* PREDEFINED SYMBOLS */

#define SP_SYMBOL "SP"
#define SP_ADDRESS 0b0
#define LCL_SYMBOL "LCL"
#define LCL_ADDRESS 0b1
#define ARG_SYMBOL "ARG"
#define ARG_VALUE 0b10
#define THIS_SYMBOL "THIS"
#define THIS_VALUE 0b11
#define THAT_SYMBOL "THAT"
#define THAT_VALUE 0b100
#define SCREEN_SYMBOL "SCREEN"
#define SCREEN_VALUE 0b0100000000000000
#define KEYBOARD_SYMBOL "KBD"
#define KEYBOARD_VALUE 0b0110000000000000

void dispose_array_of_strings(char** buffer, size_t length);
void dispose_ram_addresses(t_array_list* symbol_table, char** ram_symbols);

int sync_symbol_addresses(t_array_list* commands_buffer) {
    if (commands_buffer == NULL) {
        printf("Internal Error: null 'commands_buffer' at 'sync_symbol_addresses'.\n");
        return -1;
    }

    if (commands_buffer->type != LIST) {
        printf("Internal Error: 'commands_buffer' is not a list at 'sync_symbol_addresses'.\n");
        return -1;
    }

    t_array_list* symbol_table;

    int result = create_hash_map(&symbol_table);

    if (result < 0) {
        printf("Internal Error: failed to create 'symbol_table' at 'sync_symbol_addresses'.\n");
        return -1;
    }

    size_t sp_address = SP_ADDRESS;
    add_entry_to_array_list(symbol_table, SP_SYMBOL, strlen(SP_SYMBOL),
                            &sp_address, 1);

    size_t lcl_address = LCL_ADDRESS;
    add_entry_to_array_list(symbol_table, LCL_SYMBOL, strlen(LCL_SYMBOL),
                            &lcl_address, 1);

    size_t arg_address = ARG_VALUE;
    add_entry_to_array_list(symbol_table, ARG_SYMBOL, strlen(ARG_SYMBOL),
                            &arg_address, 1);

    size_t this_address = THIS_VALUE;
    add_entry_to_array_list(symbol_table, THIS_SYMBOL, strlen(THIS_SYMBOL),
                            &this_address, 1);

    size_t that_address = THAT_VALUE;
    add_entry_to_array_list(symbol_table, THAT_SYMBOL, strlen(THAT_SYMBOL),
                            &that_address, 1);

    size_t screen_address = SCREEN_VALUE;
    add_entry_to_array_list(symbol_table, SCREEN_SYMBOL, strlen(SCREEN_SYMBOL),
                            &screen_address, 1);

    size_t keyboard_address = KEYBOARD_VALUE;
    add_entry_to_array_list(symbol_table, KEYBOARD_SYMBOL, strlen(KEYBOARD_SYMBOL),
                            &keyboard_address, 1);

    const char RAM_START_SYMBOL = 'R';
    char** RAM_SYMBOLS = malloc(sizeof(char*) * RAM_SYMBOLS_COUNT);

    if (RAM_SYMBOLS == NULL) {
        printf("Internal Error: failed to allocate memory for 'RAM_SYMBOLS' at 'translate_instructions_into_binary'.\n");
        return -1;
    }

    for (size_t i = 0; i < RAM_SYMBOLS_COUNT; i++) {
        RAM_SYMBOLS[i] = malloc(sizeof(char) * RAM_SYMBOL_MAX_CHARACTERS * RAM_SYMBOLS_COUNT);

        if (RAM_SYMBOLS[i] == NULL) {
            dispose_array_list(symbol_table);
            dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
            free(RAM_SYMBOLS);
            printf("Internal Error: failed to allocate memory for RAM_SYMBOLS[%lu] at 'translate_instructions_into_binary'.\n", i);
            return -1;
        }

        size_t* ram_address = malloc(sizeof(size_t));

        if (ram_address == NULL) {
            printf("Internal Error: failed to allocate memory for 'ram_address' at 'translate_instructions_into_binary'.\n");
            return -1;
        }

        *(ram_address) = i;

        sprintf(RAM_SYMBOLS[i], "%c%lu", RAM_START_SYMBOL, i);

        add_entry_to_array_list(symbol_table, RAM_SYMBOLS[i], strlen(RAM_SYMBOLS[i]),
                                ram_address, 1);
    }

    const int ADDRESS_POINTER_LENGTH = 1;

    for (size_t i = 0; i < commands_buffer->length; i++) {
        t_instruction* instruction = commands_buffer->item[i];

        if (instruction == NULL) {
            dispose_ram_addresses(symbol_table, RAM_SYMBOLS);
            dispose_array_list(symbol_table);
            dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
            free(RAM_SYMBOLS);
            printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
            return -1;
        }

        if (instruction->type == L_COMMAND) {
            if (instruction->symbol == NULL) {
                dispose_array_list(symbol_table);
                dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
                free(RAM_SYMBOLS);
                printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
                return -1;
            }

            if (contains_str_key_array_list(symbol_table, instruction->symbol, instruction->symbol_length) > 0) {
                dispose_ram_addresses(symbol_table, RAM_SYMBOLS);
                dispose_array_list(symbol_table);
                dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
                free(RAM_SYMBOLS);
                printf("Error: detected a repeated symbol definition of label '%s'.\n", instruction->symbol);
                return -1;
            }

            add_entry_to_array_list(symbol_table, instruction->symbol, instruction->symbol_length,
                                    &(instruction->address), ADDRESS_POINTER_LENGTH);
        }
    }

    size_t variable_address = VARIABLE_START_ADDRESS;

    for (size_t i = 0; i < commands_buffer->length; i++) {
        t_instruction* instruction = commands_buffer->item[i];

        if (instruction == NULL) {
            dispose_ram_addresses(symbol_table, RAM_SYMBOLS);
            dispose_array_list(symbol_table);
            dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
            free(RAM_SYMBOLS);
            printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
            return -1;
        }

        if (instruction->type == A_COMMAND) {
            if (instruction->symbol == NULL) {
                dispose_ram_addresses(symbol_table, RAM_SYMBOLS);
                dispose_array_list(symbol_table);
                dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
                free(RAM_SYMBOLS);
                printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
                return -1;
            }

            char first_character = *(instruction->symbol);

            // if it's not a digit, then we are facing a reference to a label.
            if (!isdigit(first_character)) {
                result = contains_str_key_array_list(symbol_table, instruction->symbol, instruction->symbol_length);

                if (result > 0) {
                    size_t* label_address = get_value_with_str_key_from_array_list(symbol_table, instruction->symbol,
                                                                                   instruction->symbol_length);

                    if (label_address == NULL) {
                        dispose_ram_addresses(symbol_table, RAM_SYMBOLS);
                        dispose_array_list(symbol_table);
                        dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
                        free(RAM_SYMBOLS);
                        printf("Internal Error: failed to retrieve a label's address at 'sync_symbol_addresses'.\n");
                        return -1;
                    }

                    instruction->address = *(label_address);
                }
                else if (result == 0) {
                    instruction->address = variable_address;

                    add_entry_to_array_list(symbol_table, instruction->symbol, instruction->symbol_length,
                                            &instruction->address, 1);
                    variable_address++;
                }
            }
        }
    }

    dispose_array_list(symbol_table);
    dispose_array_of_strings(RAM_SYMBOLS, RAM_SYMBOLS_COUNT);
    free(RAM_SYMBOLS);
    return 1;
}

void dispose_array_of_strings(char** buffer, size_t length) {
    if (buffer != NULL) {
        for (size_t i = 0; i < length; i++) {
            if (buffer[i] != NULL) {
                free(buffer[i]);
            }
        }
    }
}

void dispose_ram_addresses(t_array_list* symbol_table, char** ram_symbols) {
    if ((symbol_table != NULL) && (ram_symbols != NULL)) {
        for (size_t i = 0; i < RAM_SYMBOLS_COUNT; i++) {
            void* address = get_value_with_str_key_from_array_list(symbol_table, ram_symbols[i],
                                                                   strlen(ram_symbols[i]));

            if (address != NULL) {
                free(address);
            }
        }
    }
}