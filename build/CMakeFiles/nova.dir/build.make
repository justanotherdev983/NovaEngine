# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bou/CLionProjects/NovaEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bou/CLionProjects/NovaEngine/build

# Include any dependencies generated for this target.
include CMakeFiles/nova.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nova.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nova.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nova.dir/flags.make

CMakeFiles/nova.dir/src/main.c.o: CMakeFiles/nova.dir/flags.make
CMakeFiles/nova.dir/src/main.c.o: ../src/main.c
CMakeFiles/nova.dir/src/main.c.o: CMakeFiles/nova.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bou/CLionProjects/NovaEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/nova.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/nova.dir/src/main.c.o -MF CMakeFiles/nova.dir/src/main.c.o.d -o CMakeFiles/nova.dir/src/main.c.o -c /home/bou/CLionProjects/NovaEngine/src/main.c

CMakeFiles/nova.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nova.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bou/CLionProjects/NovaEngine/src/main.c > CMakeFiles/nova.dir/src/main.c.i

CMakeFiles/nova.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nova.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bou/CLionProjects/NovaEngine/src/main.c -o CMakeFiles/nova.dir/src/main.c.s

CMakeFiles/nova.dir/src/game.c.o: CMakeFiles/nova.dir/flags.make
CMakeFiles/nova.dir/src/game.c.o: ../src/game.c
CMakeFiles/nova.dir/src/game.c.o: CMakeFiles/nova.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bou/CLionProjects/NovaEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/nova.dir/src/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/nova.dir/src/game.c.o -MF CMakeFiles/nova.dir/src/game.c.o.d -o CMakeFiles/nova.dir/src/game.c.o -c /home/bou/CLionProjects/NovaEngine/src/game.c

CMakeFiles/nova.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nova.dir/src/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bou/CLionProjects/NovaEngine/src/game.c > CMakeFiles/nova.dir/src/game.c.i

CMakeFiles/nova.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nova.dir/src/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bou/CLionProjects/NovaEngine/src/game.c -o CMakeFiles/nova.dir/src/game.c.s

CMakeFiles/nova.dir/src/raycast.c.o: CMakeFiles/nova.dir/flags.make
CMakeFiles/nova.dir/src/raycast.c.o: ../src/raycast.c
CMakeFiles/nova.dir/src/raycast.c.o: CMakeFiles/nova.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bou/CLionProjects/NovaEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/nova.dir/src/raycast.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/nova.dir/src/raycast.c.o -MF CMakeFiles/nova.dir/src/raycast.c.o.d -o CMakeFiles/nova.dir/src/raycast.c.o -c /home/bou/CLionProjects/NovaEngine/src/raycast.c

CMakeFiles/nova.dir/src/raycast.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nova.dir/src/raycast.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bou/CLionProjects/NovaEngine/src/raycast.c > CMakeFiles/nova.dir/src/raycast.c.i

CMakeFiles/nova.dir/src/raycast.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nova.dir/src/raycast.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bou/CLionProjects/NovaEngine/src/raycast.c -o CMakeFiles/nova.dir/src/raycast.c.s

CMakeFiles/nova.dir/src/ascii.c.o: CMakeFiles/nova.dir/flags.make
CMakeFiles/nova.dir/src/ascii.c.o: ../src/ascii.c
CMakeFiles/nova.dir/src/ascii.c.o: CMakeFiles/nova.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bou/CLionProjects/NovaEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/nova.dir/src/ascii.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/nova.dir/src/ascii.c.o -MF CMakeFiles/nova.dir/src/ascii.c.o.d -o CMakeFiles/nova.dir/src/ascii.c.o -c /home/bou/CLionProjects/NovaEngine/src/ascii.c

CMakeFiles/nova.dir/src/ascii.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nova.dir/src/ascii.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bou/CLionProjects/NovaEngine/src/ascii.c > CMakeFiles/nova.dir/src/ascii.c.i

CMakeFiles/nova.dir/src/ascii.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nova.dir/src/ascii.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bou/CLionProjects/NovaEngine/src/ascii.c -o CMakeFiles/nova.dir/src/ascii.c.s

# Object files for target nova
nova_OBJECTS = \
"CMakeFiles/nova.dir/src/main.c.o" \
"CMakeFiles/nova.dir/src/game.c.o" \
"CMakeFiles/nova.dir/src/raycast.c.o" \
"CMakeFiles/nova.dir/src/ascii.c.o"

# External object files for target nova
nova_EXTERNAL_OBJECTS =

nova: CMakeFiles/nova.dir/src/main.c.o
nova: CMakeFiles/nova.dir/src/game.c.o
nova: CMakeFiles/nova.dir/src/raycast.c.o
nova: CMakeFiles/nova.dir/src/ascii.c.o
nova: CMakeFiles/nova.dir/build.make
nova: CMakeFiles/nova.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bou/CLionProjects/NovaEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable nova"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nova.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nova.dir/build: nova
.PHONY : CMakeFiles/nova.dir/build

CMakeFiles/nova.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nova.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nova.dir/clean

CMakeFiles/nova.dir/depend:
	cd /home/bou/CLionProjects/NovaEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bou/CLionProjects/NovaEngine /home/bou/CLionProjects/NovaEngine /home/bou/CLionProjects/NovaEngine/build /home/bou/CLionProjects/NovaEngine/build /home/bou/CLionProjects/NovaEngine/build/CMakeFiles/nova.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nova.dir/depend

