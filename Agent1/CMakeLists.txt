cmake_minimum_required(VERSION 2.8.9)

project (AgentBasedModelingSim)

# Output paths
##############################################################
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Simulation Framework
##############################################################
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/LIBS)
include_directories( 
   ${CMAKE_SOURCE_DIR}/LIBS/
   ${CMAKE_SOURCE_DIR}/src
   ${CMAKE_SOURCE_DIR}/LIBS/DevIL1.6.7/include
   ${CMAKE_SOURCE_DIR}/LIBS/tinyxml
)

file(COPY LIBS DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY LIBS/glut32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY LIBS/ILU.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY LIBS/ILUT.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY LIBS/DevIL.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(Agent_SRCS
  src/drawing.h
  src/globals.h
  src/main.cpp
  src/conway.h
  src/conway.cpp
)

add_executable(Conway ${Agent_SRCS})
target_link_libraries(Conway Vfw32 DevIL ilu ilut tinyxmld_STL glut32)



# Sanitize build environment for static build with C++11
if (MSVC)
  # Disable annoying secure CRT warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")

  # We'll select the TBB library ourselves
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D__TBB_NO_IMPLICIT_LINKAGE")

  # Parallel build on MSVC (all targets)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

  if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")

    # Disable Eigen vectorization for Windows 32 bit builds (issues with unaligned access segfaults)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DEIGEN_DONT_ALIGN")
  endif()

  # Static build
  set(CompilerFlags
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
elseif(APPLE)
  # Try to auto-detect a suitable SDK
  execute_process(COMMAND bash -c "xcodebuild -version -sdk | grep MacOSX | grep Path | head -n 1 | cut -f 2 -d ' '" OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
  string(REGEX REPLACE "(\r?\n)+$" "" CMAKE_OSX_SYSROOT "${CMAKE_OSX_SYSROOT}")
  string(REGEX REPLACE "^.*X([0-9.]*).sdk$" "\\1" CMAKE_OSX_DEPLOYMENT_TARGET "${CMAKE_OSX_SYSROOT}")
endif()
