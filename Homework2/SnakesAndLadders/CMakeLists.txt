cmake_minimum_required(VERSION 2.8.9)

project (SnakesAndLadders)


include_directories( 
   ${CMAKE_CURRENT_SOURCE_DIR}/../../lecture9/external/eigen
)
add_executable(Markov test_markov.cpp TransitionMatrix.h)
set_target_properties(Markov PROPERTIES LINKER_LANGUAGE CXX)

add_executable(DTMC markov.cpp markov.h test_dtmc.cpp TransitionMatrix.h)
set_target_properties(DTMC PROPERTIES LINKER_LANGUAGE CXX)