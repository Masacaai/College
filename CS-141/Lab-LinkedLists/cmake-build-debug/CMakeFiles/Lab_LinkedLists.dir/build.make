# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/masacaai/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/masacaai/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Lab_LinkedLists.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Lab_LinkedLists.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab_LinkedLists.dir/flags.make

CMakeFiles/Lab_LinkedLists.dir/main.cpp.o: CMakeFiles/Lab_LinkedLists.dir/flags.make
CMakeFiles/Lab_LinkedLists.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab_LinkedLists.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab_LinkedLists.dir/main.cpp.o -c /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/main.cpp

CMakeFiles/Lab_LinkedLists.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_LinkedLists.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/main.cpp > CMakeFiles/Lab_LinkedLists.dir/main.cpp.i

CMakeFiles/Lab_LinkedLists.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_LinkedLists.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/main.cpp -o CMakeFiles/Lab_LinkedLists.dir/main.cpp.s

# Object files for target Lab_LinkedLists
Lab_LinkedLists_OBJECTS = \
"CMakeFiles/Lab_LinkedLists.dir/main.cpp.o"

# External object files for target Lab_LinkedLists
Lab_LinkedLists_EXTERNAL_OBJECTS =

Lab_LinkedLists: CMakeFiles/Lab_LinkedLists.dir/main.cpp.o
Lab_LinkedLists: CMakeFiles/Lab_LinkedLists.dir/build.make
Lab_LinkedLists: CMakeFiles/Lab_LinkedLists.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab_LinkedLists"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab_LinkedLists.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab_LinkedLists.dir/build: Lab_LinkedLists
.PHONY : CMakeFiles/Lab_LinkedLists.dir/build

CMakeFiles/Lab_LinkedLists.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab_LinkedLists.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab_LinkedLists.dir/clean

CMakeFiles/Lab_LinkedLists.dir/depend:
	cd /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug /home/masacaai/Code/CLionProjects/CS141/Lab-LinkedLists/cmake-build-debug/CMakeFiles/Lab_LinkedLists.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab_LinkedLists.dir/depend

