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
CMAKE_SOURCE_DIR = /nfs/homes/adamiens/42/gomoku/libs/SDL2_image

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build

# Include any dependencies generated for this target.
include CMakeFiles/showanim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/showanim.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/showanim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/showanim.dir/flags.make

CMakeFiles/showanim.dir/showanim.c.o: CMakeFiles/showanim.dir/flags.make
CMakeFiles/showanim.dir/showanim.c.o: ../showanim.c
CMakeFiles/showanim.dir/showanim.c.o: CMakeFiles/showanim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/showanim.dir/showanim.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/showanim.dir/showanim.c.o -MF CMakeFiles/showanim.dir/showanim.c.o.d -o CMakeFiles/showanim.dir/showanim.c.o -c /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/showanim.c

CMakeFiles/showanim.dir/showanim.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/showanim.dir/showanim.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/showanim.c > CMakeFiles/showanim.dir/showanim.c.i

CMakeFiles/showanim.dir/showanim.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/showanim.dir/showanim.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/showanim.c -o CMakeFiles/showanim.dir/showanim.c.s

# Object files for target showanim
showanim_OBJECTS = \
"CMakeFiles/showanim.dir/showanim.c.o"

# External object files for target showanim
showanim_EXTERNAL_OBJECTS =

showanim: CMakeFiles/showanim.dir/showanim.c.o
showanim: CMakeFiles/showanim.dir/build.make
showanim: libSDL2_image-2.0.so.0.600.3
showanim: /usr/lib/x86_64-linux-gnu/libSDL2main.a
showanim: /usr/lib/x86_64-linux-gnu/libSDL2.so
showanim: CMakeFiles/showanim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable showanim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/showanim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/showanim.dir/build: showanim
.PHONY : CMakeFiles/showanim.dir/build

CMakeFiles/showanim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/showanim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/showanim.dir/clean

CMakeFiles/showanim.dir/depend:
	cd /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nfs/homes/adamiens/42/gomoku/libs/SDL2_image /nfs/homes/adamiens/42/gomoku/libs/SDL2_image /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build /nfs/homes/adamiens/42/gomoku/libs/SDL2_image/build/CMakeFiles/showanim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/showanim.dir/depend

