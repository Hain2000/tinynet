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
include CMakeFiles/echo_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/echo_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echo_client.dir/flags.make

CMakeFiles/echo_client.dir/src/Acceptor.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Acceptor.cpp.o: ../src/Acceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/echo_client.dir/src/Acceptor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Acceptor.cpp.o -c /home/hain/tinynet/src/Acceptor.cpp

CMakeFiles/echo_client.dir/src/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Acceptor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Acceptor.cpp > CMakeFiles/echo_client.dir/src/Acceptor.cpp.i

CMakeFiles/echo_client.dir/src/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Acceptor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Acceptor.cpp -o CMakeFiles/echo_client.dir/src/Acceptor.cpp.s

CMakeFiles/echo_client.dir/src/Buffer.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Buffer.cpp.o: ../src/Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/echo_client.dir/src/Buffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Buffer.cpp.o -c /home/hain/tinynet/src/Buffer.cpp

CMakeFiles/echo_client.dir/src/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Buffer.cpp > CMakeFiles/echo_client.dir/src/Buffer.cpp.i

CMakeFiles/echo_client.dir/src/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Buffer.cpp -o CMakeFiles/echo_client.dir/src/Buffer.cpp.s

CMakeFiles/echo_client.dir/src/Connection.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Connection.cpp.o: ../src/Connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/echo_client.dir/src/Connection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Connection.cpp.o -c /home/hain/tinynet/src/Connection.cpp

CMakeFiles/echo_client.dir/src/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Connection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Connection.cpp > CMakeFiles/echo_client.dir/src/Connection.cpp.i

CMakeFiles/echo_client.dir/src/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Connection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Connection.cpp -o CMakeFiles/echo_client.dir/src/Connection.cpp.s

CMakeFiles/echo_client.dir/src/Epoll.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Epoll.cpp.o: ../src/Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/echo_client.dir/src/Epoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Epoll.cpp.o -c /home/hain/tinynet/src/Epoll.cpp

CMakeFiles/echo_client.dir/src/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Epoll.cpp > CMakeFiles/echo_client.dir/src/Epoll.cpp.i

CMakeFiles/echo_client.dir/src/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Epoll.cpp -o CMakeFiles/echo_client.dir/src/Epoll.cpp.s

CMakeFiles/echo_client.dir/src/EventLoop.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/EventLoop.cpp.o: ../src/EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/echo_client.dir/src/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/EventLoop.cpp.o -c /home/hain/tinynet/src/EventLoop.cpp

CMakeFiles/echo_client.dir/src/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/EventLoop.cpp > CMakeFiles/echo_client.dir/src/EventLoop.cpp.i

CMakeFiles/echo_client.dir/src/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/EventLoop.cpp -o CMakeFiles/echo_client.dir/src/EventLoop.cpp.s

CMakeFiles/echo_client.dir/src/Logger.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Logger.cpp.o: ../src/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/echo_client.dir/src/Logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Logger.cpp.o -c /home/hain/tinynet/src/Logger.cpp

CMakeFiles/echo_client.dir/src/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Logger.cpp > CMakeFiles/echo_client.dir/src/Logger.cpp.i

CMakeFiles/echo_client.dir/src/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Logger.cpp -o CMakeFiles/echo_client.dir/src/Logger.cpp.s

CMakeFiles/echo_client.dir/src/NetAddress.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/NetAddress.cpp.o: ../src/NetAddress.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/echo_client.dir/src/NetAddress.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/NetAddress.cpp.o -c /home/hain/tinynet/src/NetAddress.cpp

CMakeFiles/echo_client.dir/src/NetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/NetAddress.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/NetAddress.cpp > CMakeFiles/echo_client.dir/src/NetAddress.cpp.i

CMakeFiles/echo_client.dir/src/NetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/NetAddress.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/NetAddress.cpp -o CMakeFiles/echo_client.dir/src/NetAddress.cpp.s

CMakeFiles/echo_client.dir/src/Socket.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Socket.cpp.o: ../src/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/echo_client.dir/src/Socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Socket.cpp.o -c /home/hain/tinynet/src/Socket.cpp

CMakeFiles/echo_client.dir/src/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Socket.cpp > CMakeFiles/echo_client.dir/src/Socket.cpp.i

CMakeFiles/echo_client.dir/src/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Socket.cpp -o CMakeFiles/echo_client.dir/src/Socket.cpp.s

CMakeFiles/echo_client.dir/src/ThreadPool.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/ThreadPool.cpp.o: ../src/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/echo_client.dir/src/ThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/ThreadPool.cpp.o -c /home/hain/tinynet/src/ThreadPool.cpp

CMakeFiles/echo_client.dir/src/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/ThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/ThreadPool.cpp > CMakeFiles/echo_client.dir/src/ThreadPool.cpp.i

CMakeFiles/echo_client.dir/src/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/ThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/ThreadPool.cpp -o CMakeFiles/echo_client.dir/src/ThreadPool.cpp.s

CMakeFiles/echo_client.dir/src/Timer.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/src/Timer.cpp.o: ../src/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/echo_client.dir/src/Timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/src/Timer.cpp.o -c /home/hain/tinynet/src/Timer.cpp

CMakeFiles/echo_client.dir/src/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/src/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/src/Timer.cpp > CMakeFiles/echo_client.dir/src/Timer.cpp.i

CMakeFiles/echo_client.dir/src/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/src/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/src/Timer.cpp -o CMakeFiles/echo_client.dir/src/Timer.cpp.s

CMakeFiles/echo_client.dir/example/echo_client.cpp.o: CMakeFiles/echo_client.dir/flags.make
CMakeFiles/echo_client.dir/example/echo_client.cpp.o: ../example/echo_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/echo_client.dir/example/echo_client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_client.dir/example/echo_client.cpp.o -c /home/hain/tinynet/example/echo_client.cpp

CMakeFiles/echo_client.dir/example/echo_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_client.dir/example/echo_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hain/tinynet/example/echo_client.cpp > CMakeFiles/echo_client.dir/example/echo_client.cpp.i

CMakeFiles/echo_client.dir/example/echo_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_client.dir/example/echo_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hain/tinynet/example/echo_client.cpp -o CMakeFiles/echo_client.dir/example/echo_client.cpp.s

# Object files for target echo_client
echo_client_OBJECTS = \
"CMakeFiles/echo_client.dir/src/Acceptor.cpp.o" \
"CMakeFiles/echo_client.dir/src/Buffer.cpp.o" \
"CMakeFiles/echo_client.dir/src/Connection.cpp.o" \
"CMakeFiles/echo_client.dir/src/Epoll.cpp.o" \
"CMakeFiles/echo_client.dir/src/EventLoop.cpp.o" \
"CMakeFiles/echo_client.dir/src/Logger.cpp.o" \
"CMakeFiles/echo_client.dir/src/NetAddress.cpp.o" \
"CMakeFiles/echo_client.dir/src/Socket.cpp.o" \
"CMakeFiles/echo_client.dir/src/ThreadPool.cpp.o" \
"CMakeFiles/echo_client.dir/src/Timer.cpp.o" \
"CMakeFiles/echo_client.dir/example/echo_client.cpp.o"

# External object files for target echo_client
echo_client_EXTERNAL_OBJECTS =

echo_client: CMakeFiles/echo_client.dir/src/Acceptor.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/Buffer.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/Connection.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/Epoll.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/EventLoop.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/Logger.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/NetAddress.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/Socket.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/ThreadPool.cpp.o
echo_client: CMakeFiles/echo_client.dir/src/Timer.cpp.o
echo_client: CMakeFiles/echo_client.dir/example/echo_client.cpp.o
echo_client: CMakeFiles/echo_client.dir/build.make
echo_client: CMakeFiles/echo_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hain/tinynet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable echo_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echo_client.dir/build: echo_client

.PHONY : CMakeFiles/echo_client.dir/build

CMakeFiles/echo_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echo_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echo_client.dir/clean

CMakeFiles/echo_client.dir/depend:
	cd /home/hain/tinynet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hain/tinynet /home/hain/tinynet /home/hain/tinynet/build /home/hain/tinynet/build /home/hain/tinynet/build/CMakeFiles/echo_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/echo_client.dir/depend

