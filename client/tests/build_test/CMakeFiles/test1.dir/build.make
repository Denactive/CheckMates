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
CMAKE_SOURCE_DIR = /home/svetlana/tp/Chess/CheckMates/client/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/svetlana/tp/Chess/CheckMates/client/tests/build_test

# Include any dependencies generated for this target.
include CMakeFiles/test1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test1.dir/flags.make

CMakeFiles/test1.dir/tst_community.o: CMakeFiles/test1.dir/flags.make
CMakeFiles/test1.dir/tst_community.o: ../tst_community.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/client/tests/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test1.dir/tst_community.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test1.dir/tst_community.o -c /home/svetlana/tp/Chess/CheckMates/client/tests/tst_community.cpp

CMakeFiles/test1.dir/tst_community.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/tst_community.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/tests/tst_community.cpp > CMakeFiles/test1.dir/tst_community.i

CMakeFiles/test1.dir/tst_community.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/tst_community.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/tests/tst_community.cpp -o CMakeFiles/test1.dir/tst_community.s

CMakeFiles/test1.dir/main.o: CMakeFiles/test1.dir/flags.make
CMakeFiles/test1.dir/main.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/client/tests/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test1.dir/main.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test1.dir/main.o -c /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp

CMakeFiles/test1.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp > CMakeFiles/test1.dir/main.i

CMakeFiles/test1.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp -o CMakeFiles/test1.dir/main.s

CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.o: CMakeFiles/test1.dir/flags.make
CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.o: /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/client/tests/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.o -c /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp

CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp > CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.i

CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp -o CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.s

# Object files for target test1
test1_OBJECTS = \
"CMakeFiles/test1.dir/tst_community.o" \
"CMakeFiles/test1.dir/main.o" \
"CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.o"

# External object files for target test1
test1_EXTERNAL_OBJECTS =

test1: CMakeFiles/test1.dir/tst_community.o
test1: CMakeFiles/test1.dir/main.o
test1: CMakeFiles/test1.dir/home/svetlana/tp/Chess/CheckMates/client/src/community.o
test1: CMakeFiles/test1.dir/build.make
test1: CMakeFiles/test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/svetlana/tp/Chess/CheckMates/client/tests/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test1.dir/build: test1

.PHONY : CMakeFiles/test1.dir/build

CMakeFiles/test1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test1.dir/clean

CMakeFiles/test1.dir/depend:
	cd /home/svetlana/tp/Chess/CheckMates/client/tests/build_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/svetlana/tp/Chess/CheckMates/client/tests /home/svetlana/tp/Chess/CheckMates/client/tests /home/svetlana/tp/Chess/CheckMates/client/tests/build_test /home/svetlana/tp/Chess/CheckMates/client/tests/build_test /home/svetlana/tp/Chess/CheckMates/client/tests/build_test/CMakeFiles/test1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test1.dir/depend
