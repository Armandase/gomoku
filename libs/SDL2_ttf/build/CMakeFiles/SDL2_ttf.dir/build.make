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
CMAKE_SOURCE_DIR = /home/nlocusso/42/gomoku/libs/SDL2_ttf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nlocusso/42/gomoku/libs/SDL2_ttf/build

# Include any dependencies generated for this target.
include CMakeFiles/SDL2_ttf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SDL2_ttf.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SDL2_ttf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SDL2_ttf.dir/flags.make

CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o: CMakeFiles/SDL2_ttf.dir/flags.make
CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o: ../SDL_ttf.c
CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o: CMakeFiles/SDL2_ttf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nlocusso/42/gomoku/libs/SDL2_ttf/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o -MF CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o.d -o CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o -c /home/nlocusso/42/gomoku/libs/SDL2_ttf/SDL_ttf.c

CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nlocusso/42/gomoku/libs/SDL2_ttf/SDL_ttf.c > CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.i

CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nlocusso/42/gomoku/libs/SDL2_ttf/SDL_ttf.c -o CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.s

# Object files for target SDL2_ttf
SDL2_ttf_OBJECTS = \
"CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o"

# External object files for target SDL2_ttf
SDL2_ttf_EXTERNAL_OBJECTS =

libSDL2_ttf-2.0.so.0.2000.2: CMakeFiles/SDL2_ttf.dir/SDL_ttf.c.o
libSDL2_ttf-2.0.so.0.2000.2: CMakeFiles/SDL2_ttf.dir/build.make
libSDL2_ttf-2.0.so.0.2000.2: /usr/lib/x86_64-linux-gnu/libSDL2.so
libSDL2_ttf-2.0.so.0.2000.2: /usr/lib/x86_64-linux-gnu/libfreetype.so
libSDL2_ttf-2.0.so.0.2000.2: CMakeFiles/SDL2_ttf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nlocusso/42/gomoku/libs/SDL2_ttf/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libSDL2_ttf-2.0.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL2_ttf.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libSDL2_ttf-2.0.so.0.2000.2 libSDL2_ttf-2.0.so.0 libSDL2_ttf-2.0.so
	/usr/bin/cmake -E create_symlink libSDL2_ttf-2.0.so.0 libSDL2_ttf.so

libSDL2_ttf-2.0.so.0: libSDL2_ttf-2.0.so.0.2000.2
	@$(CMAKE_COMMAND) -E touch_nocreate libSDL2_ttf-2.0.so.0

libSDL2_ttf-2.0.so: libSDL2_ttf-2.0.so.0.2000.2
	@$(CMAKE_COMMAND) -E touch_nocreate libSDL2_ttf-2.0.so

# Rule to build all files generated by this target.
CMakeFiles/SDL2_ttf.dir/build: libSDL2_ttf-2.0.so
.PHONY : CMakeFiles/SDL2_ttf.dir/build

CMakeFiles/SDL2_ttf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SDL2_ttf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SDL2_ttf.dir/clean

CMakeFiles/SDL2_ttf.dir/depend:
	cd /home/nlocusso/42/gomoku/libs/SDL2_ttf/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nlocusso/42/gomoku/libs/SDL2_ttf /home/nlocusso/42/gomoku/libs/SDL2_ttf /home/nlocusso/42/gomoku/libs/SDL2_ttf/build /home/nlocusso/42/gomoku/libs/SDL2_ttf/build /home/nlocusso/42/gomoku/libs/SDL2_ttf/build/CMakeFiles/SDL2_ttf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SDL2_ttf.dir/depend

