# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds

# Include any dependencies generated for this target.
include test/CMakeFiles/test-topic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/test-topic.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test-topic.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test-topic.dir/flags.make

test/CMakeFiles/test-topic.dir/test_topic.cpp.o: test/CMakeFiles/test-topic.dir/flags.make
test/CMakeFiles/test-topic.dir/test_topic.cpp.o: /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_topic.cpp
test/CMakeFiles/test-topic.dir/test_topic.cpp.o: test/CMakeFiles/test-topic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test-topic.dir/test_topic.cpp.o"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test-topic.dir/test_topic.cpp.o -MF CMakeFiles/test-topic.dir/test_topic.cpp.o.d -o CMakeFiles/test-topic.dir/test_topic.cpp.o -c /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_topic.cpp

test/CMakeFiles/test-topic.dir/test_topic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-topic.dir/test_topic.cpp.i"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_topic.cpp > CMakeFiles/test-topic.dir/test_topic.cpp.i

test/CMakeFiles/test-topic.dir/test_topic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-topic.dir/test_topic.cpp.s"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_topic.cpp -o CMakeFiles/test-topic.dir/test_topic.cpp.s

test/CMakeFiles/test-topic.dir/test_utils.cpp.o: test/CMakeFiles/test-topic.dir/flags.make
test/CMakeFiles/test-topic.dir/test_utils.cpp.o: /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_utils.cpp
test/CMakeFiles/test-topic.dir/test_utils.cpp.o: test/CMakeFiles/test-topic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/test-topic.dir/test_utils.cpp.o"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test-topic.dir/test_utils.cpp.o -MF CMakeFiles/test-topic.dir/test_utils.cpp.o.d -o CMakeFiles/test-topic.dir/test_utils.cpp.o -c /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_utils.cpp

test/CMakeFiles/test-topic.dir/test_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-topic.dir/test_utils.cpp.i"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_utils.cpp > CMakeFiles/test-topic.dir/test_utils.cpp.i

test/CMakeFiles/test-topic.dir/test_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-topic.dir/test_utils.cpp.s"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test/test_utils.cpp -o CMakeFiles/test-topic.dir/test_utils.cpp.s

# Object files for target test-topic
test__topic_OBJECTS = \
"CMakeFiles/test-topic.dir/test_topic.cpp.o" \
"CMakeFiles/test-topic.dir/test_utils.cpp.o"

# External object files for target test-topic
test__topic_EXTERNAL_OBJECTS =

test/test-topic: test/CMakeFiles/test-topic.dir/test_topic.cpp.o
test/test-topic: test/CMakeFiles/test-topic.dir/test_utils.cpp.o
test/test-topic: test/CMakeFiles/test-topic.dir/build.make
test/test-topic: gtest/libgtest_main.a
test/test-topic: gtest/libgtest.a
test/test-topic: /home/aidan/GitHub/AidansRepo/TeensySwerve/install/microcdr/lib/libmicrocdr.a
test/test-topic: /home/aidan/GitHub/AidansRepo/TeensySwerve/install/microxrcedds_client/lib/libmicroxrcedds_client.a
test/test-topic: librmw_microxrcedds.so
test/test-topic: /opt/ros/humble/lib/librmw.so
test/test-topic: /home/aidan/GitHub/AidansRepo/TeensySwerve/install/microxrcedds_client/lib/libmicroxrcedds_client.a
test/test-topic: /home/aidan/GitHub/AidansRepo/TeensySwerve/install/microcdr/lib/libmicrocdr.a
test/test-topic: /home/aidan/GitHub/AidansRepo/TeensySwerve/install/rosidl_typesupport_microxrcedds_c/lib/librosidl_typesupport_microxrcedds_c.a
test/test-topic: /opt/ros/humble/lib/librosidl_runtime_c.so
test/test-topic: /opt/ros/humble/lib/librcutils.so
test/test-topic: test/CMakeFiles/test-topic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test-topic"
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-topic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test-topic.dir/build: test/test-topic
.PHONY : test/CMakeFiles/test-topic.dir/build

test/CMakeFiles/test-topic.dir/clean:
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test && $(CMAKE_COMMAND) -P CMakeFiles/test-topic.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test-topic.dir/clean

test/CMakeFiles/test-topic.dir/depend:
	cd /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c /home/aidan/GitHub/AidansRepo/TeensySwerve/src/uros/rmw_microxrcedds/rmw_microxrcedds_c/test /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test /home/aidan/GitHub/AidansRepo/TeensySwerve/build/rmw_microxrcedds/test/CMakeFiles/test-topic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test-topic.dir/depend

