# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build

# Include any dependencies generated for this target.
include CMakeFiles/tcp_chat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcp_chat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_chat.dir/flags.make

CMakeFiles/tcp_chat.dir/src/Client.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/Client.cpp.o: ../src/Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcp_chat.dir/src/Client.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_chat.dir/src/Client.cpp.o -c /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Client.cpp

CMakeFiles/tcp_chat.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/Client.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Client.cpp > CMakeFiles/tcp_chat.dir/src/Client.cpp.i

CMakeFiles/tcp_chat.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/Client.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Client.cpp -o CMakeFiles/tcp_chat.dir/src/Client.cpp.s

CMakeFiles/tcp_chat.dir/src/Client.cpp.o.requires:

.PHONY : CMakeFiles/tcp_chat.dir/src/Client.cpp.o.requires

CMakeFiles/tcp_chat.dir/src/Client.cpp.o.provides: CMakeFiles/tcp_chat.dir/src/Client.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_chat.dir/build.make CMakeFiles/tcp_chat.dir/src/Client.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_chat.dir/src/Client.cpp.o.provides

CMakeFiles/tcp_chat.dir/src/Client.cpp.o.provides.build: CMakeFiles/tcp_chat.dir/src/Client.cpp.o


CMakeFiles/tcp_chat.dir/src/main.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tcp_chat.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_chat.dir/src/main.cpp.o -c /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/main.cpp

CMakeFiles/tcp_chat.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/main.cpp > CMakeFiles/tcp_chat.dir/src/main.cpp.i

CMakeFiles/tcp_chat.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/main.cpp -o CMakeFiles/tcp_chat.dir/src/main.cpp.s

CMakeFiles/tcp_chat.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/tcp_chat.dir/src/main.cpp.o.requires

CMakeFiles/tcp_chat.dir/src/main.cpp.o.provides: CMakeFiles/tcp_chat.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_chat.dir/build.make CMakeFiles/tcp_chat.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_chat.dir/src/main.cpp.o.provides

CMakeFiles/tcp_chat.dir/src/main.cpp.o.provides.build: CMakeFiles/tcp_chat.dir/src/main.cpp.o


CMakeFiles/tcp_chat.dir/src/arguments.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/arguments.cpp.o: ../src/arguments.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tcp_chat.dir/src/arguments.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_chat.dir/src/arguments.cpp.o -c /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/arguments.cpp

CMakeFiles/tcp_chat.dir/src/arguments.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/arguments.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/arguments.cpp > CMakeFiles/tcp_chat.dir/src/arguments.cpp.i

CMakeFiles/tcp_chat.dir/src/arguments.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/arguments.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/arguments.cpp -o CMakeFiles/tcp_chat.dir/src/arguments.cpp.s

CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.requires:

.PHONY : CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.requires

CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.provides: CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_chat.dir/build.make CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.provides

CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.provides.build: CMakeFiles/tcp_chat.dir/src/arguments.cpp.o


CMakeFiles/tcp_chat.dir/src/Server.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/Server.cpp.o: ../src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tcp_chat.dir/src/Server.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_chat.dir/src/Server.cpp.o -c /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Server.cpp

CMakeFiles/tcp_chat.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/Server.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Server.cpp > CMakeFiles/tcp_chat.dir/src/Server.cpp.i

CMakeFiles/tcp_chat.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/Server.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Server.cpp -o CMakeFiles/tcp_chat.dir/src/Server.cpp.s

CMakeFiles/tcp_chat.dir/src/Server.cpp.o.requires:

.PHONY : CMakeFiles/tcp_chat.dir/src/Server.cpp.o.requires

CMakeFiles/tcp_chat.dir/src/Server.cpp.o.provides: CMakeFiles/tcp_chat.dir/src/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_chat.dir/build.make CMakeFiles/tcp_chat.dir/src/Server.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_chat.dir/src/Server.cpp.o.provides

CMakeFiles/tcp_chat.dir/src/Server.cpp.o.provides.build: CMakeFiles/tcp_chat.dir/src/Server.cpp.o


CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o: ../src/Server_control.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o -c /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Server_control.cpp

CMakeFiles/tcp_chat.dir/src/Server_control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/Server_control.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Server_control.cpp > CMakeFiles/tcp_chat.dir/src/Server_control.cpp.i

CMakeFiles/tcp_chat.dir/src/Server_control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/Server_control.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/Server_control.cpp -o CMakeFiles/tcp_chat.dir/src/Server_control.cpp.s

CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.requires:

.PHONY : CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.requires

CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.provides: CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_chat.dir/build.make CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.provides

CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.provides.build: CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o


CMakeFiles/tcp_chat.dir/src/User.cpp.o: CMakeFiles/tcp_chat.dir/flags.make
CMakeFiles/tcp_chat.dir/src/User.cpp.o: ../src/User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/tcp_chat.dir/src/User.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_chat.dir/src/User.cpp.o -c /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/User.cpp

CMakeFiles/tcp_chat.dir/src/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_chat.dir/src/User.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/User.cpp > CMakeFiles/tcp_chat.dir/src/User.cpp.i

CMakeFiles/tcp_chat.dir/src/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_chat.dir/src/User.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/src/User.cpp -o CMakeFiles/tcp_chat.dir/src/User.cpp.s

CMakeFiles/tcp_chat.dir/src/User.cpp.o.requires:

.PHONY : CMakeFiles/tcp_chat.dir/src/User.cpp.o.requires

CMakeFiles/tcp_chat.dir/src/User.cpp.o.provides: CMakeFiles/tcp_chat.dir/src/User.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcp_chat.dir/build.make CMakeFiles/tcp_chat.dir/src/User.cpp.o.provides.build
.PHONY : CMakeFiles/tcp_chat.dir/src/User.cpp.o.provides

CMakeFiles/tcp_chat.dir/src/User.cpp.o.provides.build: CMakeFiles/tcp_chat.dir/src/User.cpp.o


# Object files for target tcp_chat
tcp_chat_OBJECTS = \
"CMakeFiles/tcp_chat.dir/src/Client.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/main.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/arguments.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/Server.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o" \
"CMakeFiles/tcp_chat.dir/src/User.cpp.o"

# External object files for target tcp_chat
tcp_chat_EXTERNAL_OBJECTS =

tcp_chat: CMakeFiles/tcp_chat.dir/src/Client.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/main.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/arguments.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/Server.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/src/User.cpp.o
tcp_chat: CMakeFiles/tcp_chat.dir/build.make
tcp_chat: CMakeFiles/tcp_chat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable tcp_chat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_chat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_chat.dir/build: tcp_chat

.PHONY : CMakeFiles/tcp_chat.dir/build

CMakeFiles/tcp_chat.dir/requires: CMakeFiles/tcp_chat.dir/src/Client.cpp.o.requires
CMakeFiles/tcp_chat.dir/requires: CMakeFiles/tcp_chat.dir/src/main.cpp.o.requires
CMakeFiles/tcp_chat.dir/requires: CMakeFiles/tcp_chat.dir/src/arguments.cpp.o.requires
CMakeFiles/tcp_chat.dir/requires: CMakeFiles/tcp_chat.dir/src/Server.cpp.o.requires
CMakeFiles/tcp_chat.dir/requires: CMakeFiles/tcp_chat.dir/src/Server_control.cpp.o.requires
CMakeFiles/tcp_chat.dir/requires: CMakeFiles/tcp_chat.dir/src/User.cpp.o.requires

.PHONY : CMakeFiles/tcp_chat.dir/requires

CMakeFiles/tcp_chat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_chat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_chat.dir/clean

CMakeFiles/tcp_chat.dir/depend:
	cd /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build /home/andriiradiuk/Projects/MS_CPPLTRP_03/tcp_chat/build/CMakeFiles/tcp_chat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcp_chat.dir/depend

