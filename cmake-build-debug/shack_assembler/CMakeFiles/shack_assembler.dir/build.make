# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gabriel/source/shack_assembler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabriel/source/shack_assembler/cmake-build-debug

# Include any dependencies generated for this target.
include shack_assembler/CMakeFiles/shack_assembler.dir/depend.make

# Include the progress variables for this target.
include shack_assembler/CMakeFiles/shack_assembler.dir/progress.make

# Include the compile flags for this target's objects.
include shack_assembler/CMakeFiles/shack_assembler.dir/flags.make

shack_assembler/CMakeFiles/shack_assembler.dir/src/main.c.o: shack_assembler/CMakeFiles/shack_assembler.dir/flags.make
shack_assembler/CMakeFiles/shack_assembler.dir/src/main.c.o: ../shack_assembler/src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object shack_assembler/CMakeFiles/shack_assembler.dir/src/main.c.o"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shack_assembler.dir/src/main.c.o   -c /home/gabriel/source/shack_assembler/shack_assembler/src/main.c

shack_assembler/CMakeFiles/shack_assembler.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shack_assembler.dir/src/main.c.i"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/source/shack_assembler/shack_assembler/src/main.c > CMakeFiles/shack_assembler.dir/src/main.c.i

shack_assembler/CMakeFiles/shack_assembler.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shack_assembler.dir/src/main.c.s"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/source/shack_assembler/shack_assembler/src/main.c -o CMakeFiles/shack_assembler.dir/src/main.c.s

shack_assembler/CMakeFiles/shack_assembler.dir/src/general_types.c.o: shack_assembler/CMakeFiles/shack_assembler.dir/flags.make
shack_assembler/CMakeFiles/shack_assembler.dir/src/general_types.c.o: ../shack_assembler/src/general_types.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object shack_assembler/CMakeFiles/shack_assembler.dir/src/general_types.c.o"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shack_assembler.dir/src/general_types.c.o   -c /home/gabriel/source/shack_assembler/shack_assembler/src/general_types.c

shack_assembler/CMakeFiles/shack_assembler.dir/src/general_types.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shack_assembler.dir/src/general_types.c.i"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/source/shack_assembler/shack_assembler/src/general_types.c > CMakeFiles/shack_assembler.dir/src/general_types.c.i

shack_assembler/CMakeFiles/shack_assembler.dir/src/general_types.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shack_assembler.dir/src/general_types.c.s"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/source/shack_assembler/shack_assembler/src/general_types.c -o CMakeFiles/shack_assembler.dir/src/general_types.c.s

shack_assembler/CMakeFiles/shack_assembler.dir/src/instruction.c.o: shack_assembler/CMakeFiles/shack_assembler.dir/flags.make
shack_assembler/CMakeFiles/shack_assembler.dir/src/instruction.c.o: ../shack_assembler/src/instruction.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object shack_assembler/CMakeFiles/shack_assembler.dir/src/instruction.c.o"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shack_assembler.dir/src/instruction.c.o   -c /home/gabriel/source/shack_assembler/shack_assembler/src/instruction.c

shack_assembler/CMakeFiles/shack_assembler.dir/src/instruction.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shack_assembler.dir/src/instruction.c.i"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/source/shack_assembler/shack_assembler/src/instruction.c > CMakeFiles/shack_assembler.dir/src/instruction.c.i

shack_assembler/CMakeFiles/shack_assembler.dir/src/instruction.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shack_assembler.dir/src/instruction.c.s"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/source/shack_assembler/shack_assembler/src/instruction.c -o CMakeFiles/shack_assembler.dir/src/instruction.c.s

shack_assembler/CMakeFiles/shack_assembler.dir/src/assembler.c.o: shack_assembler/CMakeFiles/shack_assembler.dir/flags.make
shack_assembler/CMakeFiles/shack_assembler.dir/src/assembler.c.o: ../shack_assembler/src/assembler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object shack_assembler/CMakeFiles/shack_assembler.dir/src/assembler.c.o"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shack_assembler.dir/src/assembler.c.o   -c /home/gabriel/source/shack_assembler/shack_assembler/src/assembler.c

shack_assembler/CMakeFiles/shack_assembler.dir/src/assembler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shack_assembler.dir/src/assembler.c.i"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/source/shack_assembler/shack_assembler/src/assembler.c > CMakeFiles/shack_assembler.dir/src/assembler.c.i

shack_assembler/CMakeFiles/shack_assembler.dir/src/assembler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shack_assembler.dir/src/assembler.c.s"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/source/shack_assembler/shack_assembler/src/assembler.c -o CMakeFiles/shack_assembler.dir/src/assembler.c.s

shack_assembler/CMakeFiles/shack_assembler.dir/src/source_parser.c.o: shack_assembler/CMakeFiles/shack_assembler.dir/flags.make
shack_assembler/CMakeFiles/shack_assembler.dir/src/source_parser.c.o: ../shack_assembler/src/source_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object shack_assembler/CMakeFiles/shack_assembler.dir/src/source_parser.c.o"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shack_assembler.dir/src/source_parser.c.o   -c /home/gabriel/source/shack_assembler/shack_assembler/src/source_parser.c

shack_assembler/CMakeFiles/shack_assembler.dir/src/source_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shack_assembler.dir/src/source_parser.c.i"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/source/shack_assembler/shack_assembler/src/source_parser.c > CMakeFiles/shack_assembler.dir/src/source_parser.c.i

shack_assembler/CMakeFiles/shack_assembler.dir/src/source_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shack_assembler.dir/src/source_parser.c.s"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/source/shack_assembler/shack_assembler/src/source_parser.c -o CMakeFiles/shack_assembler.dir/src/source_parser.c.s

shack_assembler/CMakeFiles/shack_assembler.dir/src/symbol_handler.c.o: shack_assembler/CMakeFiles/shack_assembler.dir/flags.make
shack_assembler/CMakeFiles/shack_assembler.dir/src/symbol_handler.c.o: ../shack_assembler/src/symbol_handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object shack_assembler/CMakeFiles/shack_assembler.dir/src/symbol_handler.c.o"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shack_assembler.dir/src/symbol_handler.c.o   -c /home/gabriel/source/shack_assembler/shack_assembler/src/symbol_handler.c

shack_assembler/CMakeFiles/shack_assembler.dir/src/symbol_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shack_assembler.dir/src/symbol_handler.c.i"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/source/shack_assembler/shack_assembler/src/symbol_handler.c > CMakeFiles/shack_assembler.dir/src/symbol_handler.c.i

shack_assembler/CMakeFiles/shack_assembler.dir/src/symbol_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shack_assembler.dir/src/symbol_handler.c.s"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/source/shack_assembler/shack_assembler/src/symbol_handler.c -o CMakeFiles/shack_assembler.dir/src/symbol_handler.c.s

# Object files for target shack_assembler
shack_assembler_OBJECTS = \
"CMakeFiles/shack_assembler.dir/src/main.c.o" \
"CMakeFiles/shack_assembler.dir/src/general_types.c.o" \
"CMakeFiles/shack_assembler.dir/src/instruction.c.o" \
"CMakeFiles/shack_assembler.dir/src/assembler.c.o" \
"CMakeFiles/shack_assembler.dir/src/source_parser.c.o" \
"CMakeFiles/shack_assembler.dir/src/symbol_handler.c.o"

# External object files for target shack_assembler
shack_assembler_EXTERNAL_OBJECTS =

shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/src/main.c.o
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/src/general_types.c.o
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/src/instruction.c.o
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/src/assembler.c.o
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/src/source_parser.c.o
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/src/symbol_handler.c.o
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/build.make
shack_assembler/shack_assembler: shack_assembler/CMakeFiles/shack_assembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabriel/source/shack_assembler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable shack_assembler"
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shack_assembler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
shack_assembler/CMakeFiles/shack_assembler.dir/build: shack_assembler/shack_assembler

.PHONY : shack_assembler/CMakeFiles/shack_assembler.dir/build

shack_assembler/CMakeFiles/shack_assembler.dir/clean:
	cd /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler && $(CMAKE_COMMAND) -P CMakeFiles/shack_assembler.dir/cmake_clean.cmake
.PHONY : shack_assembler/CMakeFiles/shack_assembler.dir/clean

shack_assembler/CMakeFiles/shack_assembler.dir/depend:
	cd /home/gabriel/source/shack_assembler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriel/source/shack_assembler /home/gabriel/source/shack_assembler/shack_assembler /home/gabriel/source/shack_assembler/cmake-build-debug /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler /home/gabriel/source/shack_assembler/cmake-build-debug/shack_assembler/CMakeFiles/shack_assembler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : shack_assembler/CMakeFiles/shack_assembler.dir/depend

