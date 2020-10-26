//
// main.c: entry point, which handles all the incoming arguments, to the assembler.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"

int main(int argc, char** argv)
{
	if (argc > 1) {
	    const char ALL_OPERATOR = '*';
	    const char COMMAND_OPERATOR = '-';
	    const char VERBOSE_MODE_COMMAND = 'v';

	    int program_mode = 0;
	    int* index_for_file_names = malloc(sizeof(int) * argc);

	    if (index_for_file_names == NULL) {
	        printf("Internal Error: could not allocate memory for 'index_for_file_names'.\n");
	        return -1;
	    }

	    int file_count = 0;

	    /* Detect arguments which are file names, and finally detect if verbose mode is desired.*/
        for (int i = 1; i < argc; i++) {
            size_t arg_length = strlen(argv[i]);

            if (arg_length == 1) {
                if (argv[i][0] == ALL_OPERATOR) {
                    program_mode += 0b10;
                }
                else {
                    index_for_file_names[file_count] = i;
                    file_count++;
                }
            }
            else if (arg_length == 2) {
                if (argv[i][0] == COMMAND_OPERATOR) {
                    if (argv[i][1] == VERBOSE_MODE_COMMAND) {
                        program_mode += 0b1;
                    }
                    else {
                        free(index_for_file_names);
                        printf("Error: unknown command '%s'.\n", argv[i]);
                        return -1;
                    }
                }
                else {
                    index_for_file_names[file_count] = i;
                    file_count++;
                }
            }
            else if (arg_length > 2) {
                index_for_file_names[file_count] = i;
                file_count++;
            }
            else {
                free(index_for_file_names);
                printf("Error: invalid empty command.\n");
                return -1;
            }
        }

        /* Handle directory source files, or all the passed file names */
        if (program_mode >= 0b10) {
            int result = start_assembler_using_current_directory(program_mode % 2);

            if (result < 0) {
                free(index_for_file_names);
                printf("Error: failed to start assembler using current directory.\n");
                return -1;
            }
        }
        else {
            char** file_names = malloc(sizeof(char*) * file_count);

            if (file_names == NULL) {
                free(index_for_file_names);
                printf("Internal Error: failed to alloc memory for 'file_names'.\n");
                return -1;
            }

            for (int i = 0; i < file_count; i++) {
                char* file_name = argv[index_for_file_names[i]];
                file_names[i] = file_name;
            }

            int result = start_assembler(program_mode, file_count, file_names);

            if (((void*)*file_names) != ((void*)index_for_file_names)) {
                free(file_names);
            }

            if (result < 0) {
                free(index_for_file_names);
                printf("Error: failed to start assembler.\n");
                return -1;
            }
        }

        free(index_for_file_names);
	}
	else {
        printf("Error: No input file defined.\n");
        return -1;
	}

	return 0;
}