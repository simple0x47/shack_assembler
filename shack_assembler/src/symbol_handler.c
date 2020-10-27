//
// symbol_handler.c: detects symbols within a commands buffer, and proceeds to sync A_COMMANDS, references to labels,
// addresses to the referenced label ones (L_COMMAND).
//

#include <stdio.h>
#include <ctype.h>

#include "symbol_handler.h"
#include "instruction.h"

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

    const int ADDRESS_POINTER_LENGTH = 1;

    for (size_t i = 0; i < commands_buffer->length; i++) {
        t_instruction* instruction = commands_buffer->item[i];

        if (instruction == NULL) {
            dispose_array_list(symbol_table);
            printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
            return -1;
        }

        if (instruction->type == L_COMMAND) {
            if (instruction->symbol == NULL) {
                dispose_array_list(symbol_table);
                printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
                return -1;
            }

            if (contains_str_key_array_list(symbol_table, instruction->symbol, instruction->symbol_length) > 0) {
                dispose_array_list(symbol_table);
                printf("Error: detected a repeated symbol definition of label '%s'.\n", instruction->symbol);
                return -1;
            }

            add_entry_to_array_list(symbol_table, instruction->symbol, instruction->symbol_length,
                                    &(instruction->address), ADDRESS_POINTER_LENGTH);
        }
    }

    for (size_t i = 0; i < commands_buffer->length; i++) {
        t_instruction* instruction = commands_buffer->item[i];

        if (instruction == NULL) {
            dispose_array_list(symbol_table);
            printf("Internal Error: 'commands_buffer' contains invalid data at 'sync_symbol_addresses'.\n");
            return -1;
        }

        if (instruction->type == A_COMMAND) {
            if (instruction->symbol == NULL) {
                dispose_array_list(symbol_table);
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
                        dispose_array_list(symbol_table);
                        printf("Internal Error: failed to retrieve a label's address at 'sync_symbol_addresses'.\n");
                        return -1;
                    }

                    instruction->address = *(label_address);
                }
            }
        }
    }

    dispose_array_list(symbol_table);
    return 1;
}