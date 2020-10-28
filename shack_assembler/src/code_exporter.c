//
// code_exporter.c: exports the content of an array of integers into a file.
//

#include <stdio.h>
#include <string.h>

#define EXTENSION_SEPARATOR '.'
#define OUTPUT_EXTENSION "hack"
#define VALUE_OF_16_BITS 65536u

#include "code_exporter.h"

int export_instructions_to_file(const unsigned int* instructions, const char* source_file_path) {
    if (instructions == NULL) {
        printf("Internal Error: null 'instructions' at 'export_instructions_to_file'.\n");
        return -1;
    }

    if (source_file_path == NULL) {
        printf("Internal Error: null 'source_file_path' at 'export_instructions_to_file'.\n");
        return -1;
    }

    char* output_file_path = malloc(sizeof(char) * (strlen(source_file_path) + strlen(OUTPUT_EXTENSION)));

    if (output_file_path == NULL) {
        printf("Internal Error: null 'output_file_path' at 'export_instructions_to_file'.\n");
        return -1;
    }

    if (strchr(source_file_path, EXTENSION_SEPARATOR) == NULL) {
        printf("Internal Error: 'source_file_path' does not contain an extension separator at 'export_instructions_to_file'.\n");
        return -1;
    }

    size_t extension_separator_position = (strchr(source_file_path, EXTENSION_SEPARATOR) - source_file_path);

    for (size_t i = 0; i <= extension_separator_position; i++) {
        output_file_path[i] = source_file_path[i];
    }

    char* output_extension = OUTPUT_EXTENSION;

    for (size_t i = 0; i < strlen(output_extension); i++) {
        output_file_path[i + extension_separator_position + 1] = output_extension[i];
    }

    output_file_path[extension_separator_position + 1 + strlen(output_extension)] = '\0';

    FILE* output_file = fopen(output_file_path, "w");

    for (size_t i = 0; instructions[i] != -1; i++) {
        unsigned int instruction = instructions[i];

        for (int j = 0; j < 16; j++) {
            instruction = instruction << 1u;

            if (instruction & VALUE_OF_16_BITS) {
                fprintf(output_file, "1");
            }
            else {
                fprintf(output_file, "0");
            }
        }

        if (instructions[i + 1] != -1) {
            fprintf(output_file, "\n");
        }
    }

    fclose(output_file);
    return 1;
}