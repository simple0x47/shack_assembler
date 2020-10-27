//
// source_parser.h: provides a public interface for the source parser.
//

#ifndef SHACK_ASSEMBLER_SOURCE_PARSER_H
#define SHACK_ASSEMBLER_SOURCE_PARSER_H

#include "general_types.h"

int read_source_file(int verbose_mode, const char* file_path, t_array_list* commands_buffer);
int dispose_commands_from_buffer(t_array_list* commands_buffer);

#endif //SHACK_ASSEMBLER_SOURCE_PARSER_H
