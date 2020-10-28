# CMakeList.txt: proyecto de CMake para shack_assembler, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (shack_assembler "src/main.c" "src/general_types.c" src/instruction.c src/instruction.h src/assembler.h src/assembler.c src/source_parser.c src/source_parser.h src/symbol_handler.c src/symbol_handler.h src/command_transformer.c src/command_transformer.h src/code_exporter.c src/code_exporter.h)

# TODO: Agregue pruebas y destinos de instalación si es necesario.
