# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hain/tinynet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hain/tinynet/build

# Include any dependencies generated for this target.
include CMakeFiles/tinynet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tinynet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinynet.dir/flags.make

CMakeFiles/tinynet.dir/src/ThreadPool.cpp.o: CMakeFiles/tinynet.dir/flags.make
CMakeFiles/tinynet.dir/src/ThreadPool.cpp.o: ../src/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tinynet.dir/src/ThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinynet.dir/src/ThreadPool.cpp.o -c /home/hain/tinynet/src/ThreadPool.cpp

CMakeFiles/tinynet.dir/src/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinynet.dir/src/ThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/ThreadPool.cpp > CMakeFiles/tinynet.dir/src/ThreadPool.cpp.i

CMakeFiles/tinynet.dir/src/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinynet.dir/src/ThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/ThreadPool.cpp -o CMakeFiles/tinynet.dir/src/ThreadPool.cpp.s

CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.o: CMakeFiles/tinynet.dir/flags.make
CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.o: ../test1/ThreadPool_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.o -c /home/hain/tinynet/test1/ThreadPool_test.cpp

CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/test1/ThreadPool_test.cpp > CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.i

CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/test1/ThreadPool_test.cpp -o CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.s

# Object files for target tinynet
tinynet_OBJECTS = \
"CMakeFiles/tinynet.dir/src/ThreadPool.cpp.o" \
"CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.o"

# External object files for target tinynet
tinynet_EXTERNAL_OBJECTS =

tinynet: CMakeFiles/tinynet.dir/src/ThreadPool.cpp.o
tinynet: CMakeFiles/tinynet.dir/test1/ThreadPool_test.cpp.o
tinynet: CMakeFiles/tinynet.dir/build.make
tinynet: CMakeFiles/tinynet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable tinynet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinynet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinynet.dir/build: tinynet

.PHONY : CMakeFiles/tinynet.dir/build

CMakeFiles/tinynet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tinynet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tinynet.dir/clean

CMakeFiles/tinynet.dir/depend:
	cd /home/hain/tinynet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hain/tinynet /home/hain/tinynet /home/hain/tinynet/build /home/hain/tinynet/build /home/hain/tinynet/build/CMakeFiles/tinynet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tinynet.dir/depend

