# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/maddiejuarez/Documents/comp310/comp310project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/maddiejuarez/Documents/comp310/comp310project/build

# Include any dependencies generated for this target.
include CMakeFiles/r-forth.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/r-forth.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/r-forth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/r-forth.dir/flags.make

CMakeFiles/r-forth.dir/r-forth.cpp.o: CMakeFiles/r-forth.dir/flags.make
CMakeFiles/r-forth.dir/r-forth.cpp.o: /Users/maddiejuarez/Documents/comp310/comp310project/r-forth.cpp
CMakeFiles/r-forth.dir/r-forth.cpp.o: CMakeFiles/r-forth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/maddiejuarez/Documents/comp310/comp310project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/r-forth.dir/r-forth.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/r-forth.dir/r-forth.cpp.o -MF CMakeFiles/r-forth.dir/r-forth.cpp.o.d -o CMakeFiles/r-forth.dir/r-forth.cpp.o -c /Users/maddiejuarez/Documents/comp310/comp310project/r-forth.cpp

CMakeFiles/r-forth.dir/r-forth.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-forth.dir/r-forth.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maddiejuarez/Documents/comp310/comp310project/r-forth.cpp > CMakeFiles/r-forth.dir/r-forth.cpp.i

CMakeFiles/r-forth.dir/r-forth.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-forth.dir/r-forth.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maddiejuarez/Documents/comp310/comp310project/r-forth.cpp -o CMakeFiles/r-forth.dir/r-forth.cpp.s

CMakeFiles/r-forth.dir/int_stack.cpp.o: CMakeFiles/r-forth.dir/flags.make
CMakeFiles/r-forth.dir/int_stack.cpp.o: /Users/maddiejuarez/Documents/comp310/comp310project/int_stack.cpp
CMakeFiles/r-forth.dir/int_stack.cpp.o: CMakeFiles/r-forth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/maddiejuarez/Documents/comp310/comp310project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/r-forth.dir/int_stack.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/r-forth.dir/int_stack.cpp.o -MF CMakeFiles/r-forth.dir/int_stack.cpp.o.d -o CMakeFiles/r-forth.dir/int_stack.cpp.o -c /Users/maddiejuarez/Documents/comp310/comp310project/int_stack.cpp

CMakeFiles/r-forth.dir/int_stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-forth.dir/int_stack.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maddiejuarez/Documents/comp310/comp310project/int_stack.cpp > CMakeFiles/r-forth.dir/int_stack.cpp.i

CMakeFiles/r-forth.dir/int_stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-forth.dir/int_stack.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maddiejuarez/Documents/comp310/comp310project/int_stack.cpp -o CMakeFiles/r-forth.dir/int_stack.cpp.s

CMakeFiles/r-forth.dir/token.cpp.o: CMakeFiles/r-forth.dir/flags.make
CMakeFiles/r-forth.dir/token.cpp.o: /Users/maddiejuarez/Documents/comp310/comp310project/token.cpp
CMakeFiles/r-forth.dir/token.cpp.o: CMakeFiles/r-forth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/maddiejuarez/Documents/comp310/comp310project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/r-forth.dir/token.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/r-forth.dir/token.cpp.o -MF CMakeFiles/r-forth.dir/token.cpp.o.d -o CMakeFiles/r-forth.dir/token.cpp.o -c /Users/maddiejuarez/Documents/comp310/comp310project/token.cpp

CMakeFiles/r-forth.dir/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-forth.dir/token.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maddiejuarez/Documents/comp310/comp310project/token.cpp > CMakeFiles/r-forth.dir/token.cpp.i

CMakeFiles/r-forth.dir/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-forth.dir/token.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maddiejuarez/Documents/comp310/comp310project/token.cpp -o CMakeFiles/r-forth.dir/token.cpp.s

# Object files for target r-forth
r__forth_OBJECTS = \
"CMakeFiles/r-forth.dir/r-forth.cpp.o" \
"CMakeFiles/r-forth.dir/int_stack.cpp.o" \
"CMakeFiles/r-forth.dir/token.cpp.o"

# External object files for target r-forth
r__forth_EXTERNAL_OBJECTS =

r-forth: CMakeFiles/r-forth.dir/r-forth.cpp.o
r-forth: CMakeFiles/r-forth.dir/int_stack.cpp.o
r-forth: CMakeFiles/r-forth.dir/token.cpp.o
r-forth: CMakeFiles/r-forth.dir/build.make
r-forth: CMakeFiles/r-forth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/maddiejuarez/Documents/comp310/comp310project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable r-forth"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/r-forth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/r-forth.dir/build: r-forth
.PHONY : CMakeFiles/r-forth.dir/build

CMakeFiles/r-forth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/r-forth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/r-forth.dir/clean

CMakeFiles/r-forth.dir/depend:
	cd /Users/maddiejuarez/Documents/comp310/comp310project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/maddiejuarez/Documents/comp310/comp310project /Users/maddiejuarez/Documents/comp310/comp310project /Users/maddiejuarez/Documents/comp310/comp310project/build /Users/maddiejuarez/Documents/comp310/comp310project/build /Users/maddiejuarez/Documents/comp310/comp310project/build/CMakeFiles/r-forth.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/r-forth.dir/depend

