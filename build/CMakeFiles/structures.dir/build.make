# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Utente\Desktop\Data-Structures

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Utente\Desktop\Data-Structures\build

# Include any dependencies generated for this target.
include CMakeFiles/structures.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/structures.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/structures.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/structures.dir/flags.make

CMakeFiles/structures.dir/tester.cpp.obj: CMakeFiles/structures.dir/flags.make
CMakeFiles/structures.dir/tester.cpp.obj: ../tester.cpp
CMakeFiles/structures.dir/tester.cpp.obj: CMakeFiles/structures.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Utente\Desktop\Data-Structures\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/structures.dir/tester.cpp.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/structures.dir/tester.cpp.obj -MF CMakeFiles\structures.dir\tester.cpp.obj.d -o CMakeFiles\structures.dir\tester.cpp.obj -c C:\Users\Utente\Desktop\Data-Structures\tester.cpp

CMakeFiles/structures.dir/tester.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/structures.dir/tester.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Utente\Desktop\Data-Structures\tester.cpp > CMakeFiles\structures.dir\tester.cpp.i

CMakeFiles/structures.dir/tester.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/structures.dir/tester.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Utente\Desktop\Data-Structures\tester.cpp -o CMakeFiles\structures.dir\tester.cpp.s

# Object files for target structures
structures_OBJECTS = \
"CMakeFiles/structures.dir/tester.cpp.obj"

# External object files for target structures
structures_EXTERNAL_OBJECTS =

structures.exe: CMakeFiles/structures.dir/tester.cpp.obj
structures.exe: CMakeFiles/structures.dir/build.make
structures.exe: CMakeFiles/structures.dir/linklibs.rsp
structures.exe: CMakeFiles/structures.dir/objects1.rsp
structures.exe: CMakeFiles/structures.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Utente\Desktop\Data-Structures\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable structures.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\structures.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/structures.dir/build: structures.exe
.PHONY : CMakeFiles/structures.dir/build

CMakeFiles/structures.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\structures.dir\cmake_clean.cmake
.PHONY : CMakeFiles/structures.dir/clean

CMakeFiles/structures.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Utente\Desktop\Data-Structures C:\Users\Utente\Desktop\Data-Structures C:\Users\Utente\Desktop\Data-Structures\build C:\Users\Utente\Desktop\Data-Structures\build C:\Users\Utente\Desktop\Data-Structures\build\CMakeFiles\structures.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/structures.dir/depend
