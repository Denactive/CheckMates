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
CMAKE_SOURCE_DIR = /home/svetlana/tp/Chess/CheckMates/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/model_view_playground.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/model_view_playground.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/model_view_playground.dir/flags.make

CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.o: model_view_playground_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.o -c /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/model_view_playground_autogen/mocs_compilation.cpp

CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/model_view_playground_autogen/mocs_compilation.cpp > CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.i

CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/model_view_playground_autogen/mocs_compilation.cpp -o CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.s

CMakeFiles/model_view_playground.dir/src/database.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/database.o: /home/svetlana/tp/Chess/CheckMates/client/src/database.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/model_view_playground.dir/src/database.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/database.o -c /home/svetlana/tp/Chess/CheckMates/client/src/database.cpp

CMakeFiles/model_view_playground.dir/src/database.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/database.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/database.cpp > CMakeFiles/model_view_playground.dir/src/database.i

CMakeFiles/model_view_playground.dir/src/database.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/database.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/database.cpp -o CMakeFiles/model_view_playground.dir/src/database.s

CMakeFiles/model_view_playground.dir/src/chessboard.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/chessboard.o: /home/svetlana/tp/Chess/CheckMates/client/src/chessboard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/model_view_playground.dir/src/chessboard.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/chessboard.o -c /home/svetlana/tp/Chess/CheckMates/client/src/chessboard.cpp

CMakeFiles/model_view_playground.dir/src/chessboard.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/chessboard.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/chessboard.cpp > CMakeFiles/model_view_playground.dir/src/chessboard.i

CMakeFiles/model_view_playground.dir/src/chessboard.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/chessboard.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/chessboard.cpp -o CMakeFiles/model_view_playground.dir/src/chessboard.s

CMakeFiles/model_view_playground.dir/src/community.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/community.o: /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/model_view_playground.dir/src/community.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/community.o -c /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp

CMakeFiles/model_view_playground.dir/src/community.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/community.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp > CMakeFiles/model_view_playground.dir/src/community.i

CMakeFiles/model_view_playground.dir/src/community.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/community.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/community.cpp -o CMakeFiles/model_view_playground.dir/src/community.s

CMakeFiles/model_view_playground.dir/src/figures.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/figures.o: /home/svetlana/tp/Chess/CheckMates/client/src/figures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/model_view_playground.dir/src/figures.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/figures.o -c /home/svetlana/tp/Chess/CheckMates/client/src/figures.cpp

CMakeFiles/model_view_playground.dir/src/figures.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/figures.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/figures.cpp > CMakeFiles/model_view_playground.dir/src/figures.i

CMakeFiles/model_view_playground.dir/src/figures.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/figures.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/figures.cpp -o CMakeFiles/model_view_playground.dir/src/figures.s

CMakeFiles/model_view_playground.dir/src/gamewindowswork.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/gamewindowswork.o: /home/svetlana/tp/Chess/CheckMates/client/src/gamewindowswork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/model_view_playground.dir/src/gamewindowswork.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/gamewindowswork.o -c /home/svetlana/tp/Chess/CheckMates/client/src/gamewindowswork.cpp

CMakeFiles/model_view_playground.dir/src/gamewindowswork.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/gamewindowswork.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/gamewindowswork.cpp > CMakeFiles/model_view_playground.dir/src/gamewindowswork.i

CMakeFiles/model_view_playground.dir/src/gamewindowswork.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/gamewindowswork.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/gamewindowswork.cpp -o CMakeFiles/model_view_playground.dir/src/gamewindowswork.s

CMakeFiles/model_view_playground.dir/src/graphics.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/graphics.o: /home/svetlana/tp/Chess/CheckMates/client/src/graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/model_view_playground.dir/src/graphics.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/graphics.o -c /home/svetlana/tp/Chess/CheckMates/client/src/graphics.cpp

CMakeFiles/model_view_playground.dir/src/graphics.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/graphics.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/graphics.cpp > CMakeFiles/model_view_playground.dir/src/graphics.i

CMakeFiles/model_view_playground.dir/src/graphics.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/graphics.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/graphics.cpp -o CMakeFiles/model_view_playground.dir/src/graphics.s

CMakeFiles/model_view_playground.dir/src/main.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/main.o: /home/svetlana/tp/Chess/CheckMates/client/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/model_view_playground.dir/src/main.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/main.o -c /home/svetlana/tp/Chess/CheckMates/client/src/main.cpp

CMakeFiles/model_view_playground.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/main.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/main.cpp > CMakeFiles/model_view_playground.dir/src/main.i

CMakeFiles/model_view_playground.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/main.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/main.cpp -o CMakeFiles/model_view_playground.dir/src/main.s

CMakeFiles/model_view_playground.dir/src/mainwindow.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/src/mainwindow.o: /home/svetlana/tp/Chess/CheckMates/client/src/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/model_view_playground.dir/src/mainwindow.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/src/mainwindow.o -c /home/svetlana/tp/Chess/CheckMates/client/src/mainwindow.cpp

CMakeFiles/model_view_playground.dir/src/mainwindow.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/src/mainwindow.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/src/mainwindow.cpp > CMakeFiles/model_view_playground.dir/src/mainwindow.i

CMakeFiles/model_view_playground.dir/src/mainwindow.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/src/mainwindow.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/src/mainwindow.cpp -o CMakeFiles/model_view_playground.dir/src/mainwindow.s

CMakeFiles/model_view_playground.dir/tests/main.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/tests/main.o: /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/model_view_playground.dir/tests/main.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/tests/main.o -c /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp

CMakeFiles/model_view_playground.dir/tests/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/tests/main.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp > CMakeFiles/model_view_playground.dir/tests/main.i

CMakeFiles/model_view_playground.dir/tests/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/tests/main.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/tests/main.cpp -o CMakeFiles/model_view_playground.dir/tests/main.s

CMakeFiles/model_view_playground.dir/tests/tests.o: CMakeFiles/model_view_playground.dir/flags.make
CMakeFiles/model_view_playground.dir/tests/tests.o: /home/svetlana/tp/Chess/CheckMates/client/tests/tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/model_view_playground.dir/tests/tests.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_view_playground.dir/tests/tests.o -c /home/svetlana/tp/Chess/CheckMates/client/tests/tests.cpp

CMakeFiles/model_view_playground.dir/tests/tests.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_view_playground.dir/tests/tests.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/svetlana/tp/Chess/CheckMates/client/tests/tests.cpp > CMakeFiles/model_view_playground.dir/tests/tests.i

CMakeFiles/model_view_playground.dir/tests/tests.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_view_playground.dir/tests/tests.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/svetlana/tp/Chess/CheckMates/client/tests/tests.cpp -o CMakeFiles/model_view_playground.dir/tests/tests.s

# Object files for target model_view_playground
model_view_playground_OBJECTS = \
"CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.o" \
"CMakeFiles/model_view_playground.dir/src/database.o" \
"CMakeFiles/model_view_playground.dir/src/chessboard.o" \
"CMakeFiles/model_view_playground.dir/src/community.o" \
"CMakeFiles/model_view_playground.dir/src/figures.o" \
"CMakeFiles/model_view_playground.dir/src/gamewindowswork.o" \
"CMakeFiles/model_view_playground.dir/src/graphics.o" \
"CMakeFiles/model_view_playground.dir/src/main.o" \
"CMakeFiles/model_view_playground.dir/src/mainwindow.o" \
"CMakeFiles/model_view_playground.dir/tests/main.o" \
"CMakeFiles/model_view_playground.dir/tests/tests.o"

# External object files for target model_view_playground
model_view_playground_EXTERNAL_OBJECTS =

model_view_playground: CMakeFiles/model_view_playground.dir/model_view_playground_autogen/mocs_compilation.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/database.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/chessboard.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/community.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/figures.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/gamewindowswork.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/graphics.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/main.o
model_view_playground: CMakeFiles/model_view_playground.dir/src/mainwindow.o
model_view_playground: CMakeFiles/model_view_playground.dir/tests/main.o
model_view_playground: CMakeFiles/model_view_playground.dir/tests/tests.o
model_view_playground: CMakeFiles/model_view_playground.dir/build.make
model_view_playground: CMakeFiles/model_view_playground.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable model_view_playground"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/model_view_playground.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/model_view_playground.dir/build: model_view_playground

.PHONY : CMakeFiles/model_view_playground.dir/build

CMakeFiles/model_view_playground.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/model_view_playground.dir/cmake_clean.cmake
.PHONY : CMakeFiles/model_view_playground.dir/clean

CMakeFiles/model_view_playground.dir/depend:
	cd /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/svetlana/tp/Chess/CheckMates/client /home/svetlana/tp/Chess/CheckMates/client /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug /home/svetlana/tp/Chess/CheckMates/build-client-Desktop-Debug/CMakeFiles/model_view_playground.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/model_view_playground.dir/depend

