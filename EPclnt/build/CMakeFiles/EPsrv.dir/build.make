# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Projects\otus_3tsk\EPclnt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Projects\otus_3tsk\EPclnt\build

# Include any dependencies generated for this target.
include CMakeFiles/EPsrv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/EPsrv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/EPsrv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EPsrv.dir/flags.make

CMakeFiles/EPsrv.dir/codegen:
.PHONY : CMakeFiles/EPsrv.dir/codegen

CMakeFiles/EPsrv.dir/main.cpp.obj: CMakeFiles/EPsrv.dir/flags.make
CMakeFiles/EPsrv.dir/main.cpp.obj: C:/Projects/otus_3tsk/EPclnt/main.cpp
CMakeFiles/EPsrv.dir/main.cpp.obj: CMakeFiles/EPsrv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Projects\otus_3tsk\EPclnt\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EPsrv.dir/main.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/EPsrv.dir/main.cpp.obj -MF CMakeFiles\EPsrv.dir\main.cpp.obj.d -o CMakeFiles\EPsrv.dir\main.cpp.obj -c C:\Projects\otus_3tsk\EPclnt\main.cpp

CMakeFiles/EPsrv.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/EPsrv.dir/main.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Projects\otus_3tsk\EPclnt\main.cpp > CMakeFiles\EPsrv.dir\main.cpp.i

CMakeFiles/EPsrv.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/EPsrv.dir/main.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Projects\otus_3tsk\EPclnt\main.cpp -o CMakeFiles\EPsrv.dir\main.cpp.s

# Object files for target EPsrv
EPsrv_OBJECTS = \
"CMakeFiles/EPsrv.dir/main.cpp.obj"

# External object files for target EPsrv
EPsrv_EXTERNAL_OBJECTS =

EPsrv.exe: CMakeFiles/EPsrv.dir/main.cpp.obj
EPsrv.exe: CMakeFiles/EPsrv.dir/build.make
EPsrv.exe: CMakeFiles/EPsrv.dir/linkLibs.rsp
EPsrv.exe: CMakeFiles/EPsrv.dir/objects1.rsp
EPsrv.exe: CMakeFiles/EPsrv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Projects\otus_3tsk\EPclnt\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EPsrv.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\EPsrv.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EPsrv.dir/build: EPsrv.exe
.PHONY : CMakeFiles/EPsrv.dir/build

CMakeFiles/EPsrv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\EPsrv.dir\cmake_clean.cmake
.PHONY : CMakeFiles/EPsrv.dir/clean

CMakeFiles/EPsrv.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Projects\otus_3tsk\EPclnt C:\Projects\otus_3tsk\EPclnt C:\Projects\otus_3tsk\EPclnt\build C:\Projects\otus_3tsk\EPclnt\build C:\Projects\otus_3tsk\EPclnt\build\CMakeFiles\EPsrv.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/EPsrv.dir/depend

