//
// assembler.h: provides the 'public' interface for the assembler module.
//

#ifndef SHACK_ASSEMBLER_ASSEMBLER_H
#define SHACK_ASSEMBLER_ASSEMBLER_H

#define MAX_CHARACTERS_FILE_NAME 255

int start_assembler(int verbose_mode, int file_count, char** file_names);
int start_assembler_using_current_directory(int verbose_mode);

#endif //SHACK_ASSEMBLER_ASSEMBLER_H
