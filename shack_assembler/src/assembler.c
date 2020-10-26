//
// assembler.c: organizes and delegates the assembling process.
//

#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "assembler.h"
#include "general_types.h"
#include "source_parser.h"

int handle_source_file(int verbose_mode, const char* file_path);

int start_assembler(int verbose_mode, int file_count, char** file_names) {
    if (file_count <= 0) {
        printf("Internal Error: 'file_count' is equal to, or below, 0 at 'start_assembler'.\n");
        return -1;
    }

    if (file_names == NULL) {
        printf("Internal Error: 'file_names' is NULL at 'start_assembler'.\n");
        return -1;
    }

    for (int i = 0; i < file_count; i++) {
        char* file_name = file_names[i];

        if (file_name == NULL) {
            printf("Internal Error: 'file_names' contains NULL values at 'start_assembler'.\n");
            return -1;
        }

        int result = handle_source_file(verbose_mode, file_name);

        if (result < 0) {
            printf("Error: failed to handle source file '%s' at 'start_assembler'.\n", file_name);
        }
    }

    return 1;
}

int start_assembler_using_current_directory(int verbose_mode) {
    const char* CURRENT_DIRECTORY = ".";
    DIR* directory = opendir(CURRENT_DIRECTORY);

    if (directory == NULL) {
        printf("Internal Error: could not open the current directory at 'start_assembler_using_current_directory'.\n");
        return -1;
    }

    const int FILE_EXTENSION_LENGTH = 4;

    struct dirent* directory_entry = readdir(directory);
    while (directory_entry) {
        /* If it's an 'asm' file type, handles it. */
        if (directory_entry->d_type == DT_REG) {
            size_t file_name_length = strlen(directory_entry->d_name);

            if (file_name_length > FILE_EXTENSION_LENGTH) {
                char* file_name = directory_entry->d_name;

                if ((file_name[file_name_length - 4] == '.') &&
                    ((file_name[file_name_length - 3] == 'a') || (file_name[file_name_length - 3] == 'A')) &&
                    ((file_name[file_name_length - 2] == 's') || (file_name[file_name_length - 2] == 'S')) &&
                    ((file_name[file_name_length - 1] == 'm') || (file_name[file_name_length - 1] == 'M'))) {
                    int result = handle_source_file(verbose_mode, file_name);

                    if (result == -1) {
                        printf("Error: failed to treat source file '%s' at 'start_assembler_using_current_directory'.\n",
                               file_name);
                    }
                }
            }
        }

        directory_entry = readdir(directory);
    }

    return 1;
}

int handle_source_file(int verbose_mode, const char* file_path) {
    if (file_path == NULL) {
        printf("Internal Error: 'file_path' is null at 'handle_source_file'.\n");
        return -1;
    }

    t_array_list* commands_buffer;

    int result = create_array_list(&commands_buffer);

    if (result < 0) {
        printf("Internal Error: failed to create an array list at 'handle_source_file'.\n");
        return -1;
    }

    result = read_source_file(verbose_mode, file_path, commands_buffer);

    if (result < 0) {
        printf("Internal Error: failed to read source file '%s' at 'handle_source_file'.\n", file_path);
        return -1;
    }

    dispose_array_list(commands_buffer);

    return 1;
}