# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /cygdrive/c/Users/aradiuk/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/aradiuk/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Wolf3d.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Wolf3d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Wolf3d.dir/flags.make

CMakeFiles/Wolf3d.dir/src/main.c.o: CMakeFiles/Wolf3d.dir/flags.make
CMakeFiles/Wolf3d.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Wolf3d.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Wolf3d.dir/src/main.c.o   -c "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/main.c"

CMakeFiles/Wolf3d.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Wolf3d.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/main.c" > CMakeFiles/Wolf3d.dir/src/main.c.i

CMakeFiles/Wolf3d.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Wolf3d.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/main.c" -o CMakeFiles/Wolf3d.dir/src/main.c.s

CMakeFiles/Wolf3d.dir/src/keyhooks.c.o: CMakeFiles/Wolf3d.dir/flags.make
CMakeFiles/Wolf3d.dir/src/keyhooks.c.o: ../src/keyhooks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Wolf3d.dir/src/keyhooks.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Wolf3d.dir/src/keyhooks.c.o   -c "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/keyhooks.c"

CMakeFiles/Wolf3d.dir/src/keyhooks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Wolf3d.dir/src/keyhooks.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/keyhooks.c" > CMakeFiles/Wolf3d.dir/src/keyhooks.c.i

CMakeFiles/Wolf3d.dir/src/keyhooks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Wolf3d.dir/src/keyhooks.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/keyhooks.c" -o CMakeFiles/Wolf3d.dir/src/keyhooks.c.s

CMakeFiles/Wolf3d.dir/src/map_reading.c.o: CMakeFiles/Wolf3d.dir/flags.make
CMakeFiles/Wolf3d.dir/src/map_reading.c.o: ../src/map_reading.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Wolf3d.dir/src/map_reading.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Wolf3d.dir/src/map_reading.c.o   -c "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/map_reading.c"

CMakeFiles/Wolf3d.dir/src/map_reading.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Wolf3d.dir/src/map_reading.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/map_reading.c" > CMakeFiles/Wolf3d.dir/src/map_reading.c.i

CMakeFiles/Wolf3d.dir/src/map_reading.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Wolf3d.dir/src/map_reading.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/map_reading.c" -o CMakeFiles/Wolf3d.dir/src/map_reading.c.s

CMakeFiles/Wolf3d.dir/src/environment.c.o: CMakeFiles/Wolf3d.dir/flags.make
CMakeFiles/Wolf3d.dir/src/environment.c.o: ../src/environment.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Wolf3d.dir/src/environment.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Wolf3d.dir/src/environment.c.o   -c "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/environment.c"

CMakeFiles/Wolf3d.dir/src/environment.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Wolf3d.dir/src/environment.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/environment.c" > CMakeFiles/Wolf3d.dir/src/environment.c.i

CMakeFiles/Wolf3d.dir/src/environment.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Wolf3d.dir/src/environment.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/environment.c" -o CMakeFiles/Wolf3d.dir/src/environment.c.s

CMakeFiles/Wolf3d.dir/src/raycasting.c.o: CMakeFiles/Wolf3d.dir/flags.make
CMakeFiles/Wolf3d.dir/src/raycasting.c.o: ../src/raycasting.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Wolf3d.dir/src/raycasting.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Wolf3d.dir/src/raycasting.c.o   -c "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/raycasting.c"

CMakeFiles/Wolf3d.dir/src/raycasting.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Wolf3d.dir/src/raycasting.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/raycasting.c" > CMakeFiles/Wolf3d.dir/src/raycasting.c.i

CMakeFiles/Wolf3d.dir/src/raycasting.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Wolf3d.dir/src/raycasting.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/src/raycasting.c" -o CMakeFiles/Wolf3d.dir/src/raycasting.c.s

# Object files for target Wolf3d
Wolf3d_OBJECTS = \
"CMakeFiles/Wolf3d.dir/src/main.c.o" \
"CMakeFiles/Wolf3d.dir/src/keyhooks.c.o" \
"CMakeFiles/Wolf3d.dir/src/map_reading.c.o" \
"CMakeFiles/Wolf3d.dir/src/environment.c.o" \
"CMakeFiles/Wolf3d.dir/src/raycasting.c.o"

# External object files for target Wolf3d
Wolf3d_EXTERNAL_OBJECTS =

Wolf3d.exe: CMakeFiles/Wolf3d.dir/src/main.c.o
Wolf3d.exe: CMakeFiles/Wolf3d.dir/src/keyhooks.c.o
Wolf3d.exe: CMakeFiles/Wolf3d.dir/src/map_reading.c.o
Wolf3d.exe: CMakeFiles/Wolf3d.dir/src/environment.c.o
Wolf3d.exe: CMakeFiles/Wolf3d.dir/src/raycasting.c.o
Wolf3d.exe: CMakeFiles/Wolf3d.dir/build.make
Wolf3d.exe: CMakeFiles/Wolf3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable Wolf3d.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Wolf3d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Wolf3d.dir/build: Wolf3d.exe

.PHONY : CMakeFiles/Wolf3d.dir/build

CMakeFiles/Wolf3d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Wolf3d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Wolf3d.dir/clean

CMakeFiles/Wolf3d.dir/depend:
	cd "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d" "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d" "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug" "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug" "/cygdrive/c/Users/aradiuk/Desktop/Shared folder/AbstractVM/Projects/Wolf3d/cmake-build-debug/CMakeFiles/Wolf3d.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Wolf3d.dir/depend

