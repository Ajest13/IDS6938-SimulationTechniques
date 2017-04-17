cmake_minimum_required(VERSION 3.1.0)

project (BehaviorFramework)

# Output paths
##############################################################
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/LIBS)
include_directories( 
   ${CMAKE_SOURCE_DIR}/LIBS/
   ${CMAKE_SOURCE_DIR}/src
)

file(COPY LIBS DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY LIBS/glut32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES src/*.cpp src/*.h)
file(GLOB RESOURCESFILES res/*.*)



# set MFC attributes
set(CMAKE_MFC_FLAG 2) # 2 if use MFC as dll
ADD_DEFINITIONS(-D_AFXDLL) # if use MFC as dll



add_executable(Flocking WIN32 ${SOURCES} ${RESOURCESFILES} Behavior.rc)
target_link_libraries(Flocking glut32)
set_target_properties(Flocking PROPERTIES LINKER_LANGUAGE CXX)