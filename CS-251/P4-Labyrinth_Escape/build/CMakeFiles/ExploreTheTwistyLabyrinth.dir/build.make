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
CMAKE_COMMAND = /nix/store/sgsvy949kd2sr2vsxcffz5jkv855rmib-cmake-3.22.2/bin/cmake

# The command to remove a file.
RM = /nix/store/sgsvy949kd2sr2vsxcffz5jkv855rmib-cmake-3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/masacaai/Code/CS-251/P4-Labyrinth_Escape

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build

# Include any dependencies generated for this target.
include CMakeFiles/ExploreTheTwistyLabyrinth.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ExploreTheTwistyLabyrinth.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ExploreTheTwistyLabyrinth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ExploreTheTwistyLabyrinth.dir/flags.make

CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o: CMakeFiles/ExploreTheTwistyLabyrinth.dir/flags.make
CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o: ../ExploreTheTwistyLabyrinth.cpp
CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o: CMakeFiles/ExploreTheTwistyLabyrinth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o -MF CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o.d -o CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o -c /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/ExploreTheTwistyLabyrinth.cpp

CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/ExploreTheTwistyLabyrinth.cpp > CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.i

CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/ExploreTheTwistyLabyrinth.cpp -o CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.s

# Object files for target ExploreTheTwistyLabyrinth
ExploreTheTwistyLabyrinth_OBJECTS = \
"CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o"

# External object files for target ExploreTheTwistyLabyrinth
ExploreTheTwistyLabyrinth_EXTERNAL_OBJECTS =

ExploreTheTwistyLabyrinth: CMakeFiles/ExploreTheTwistyLabyrinth.dir/ExploreTheTwistyLabyrinth.cpp.o
ExploreTheTwistyLabyrinth: CMakeFiles/ExploreTheTwistyLabyrinth.dir/build.make
ExploreTheTwistyLabyrinth: CMakeFiles/ExploreTheTwistyLabyrinth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ExploreTheTwistyLabyrinth"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ExploreTheTwistyLabyrinth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ExploreTheTwistyLabyrinth.dir/build: ExploreTheTwistyLabyrinth
.PHONY : CMakeFiles/ExploreTheTwistyLabyrinth.dir/build

CMakeFiles/ExploreTheTwistyLabyrinth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExploreTheTwistyLabyrinth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExploreTheTwistyLabyrinth.dir/clean

CMakeFiles/ExploreTheTwistyLabyrinth.dir/depend:
	cd /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masacaai/Code/CS-251/P4-Labyrinth_Escape /home/masacaai/Code/CS-251/P4-Labyrinth_Escape /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build /home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build/CMakeFiles/ExploreTheTwistyLabyrinth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExploreTheTwistyLabyrinth.dir/depend

