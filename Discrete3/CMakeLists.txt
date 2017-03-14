cmake_minimum_required(VERSION 2.8.9)

project (Discrete3)


add_executable(MarkovDTMC markov.cpp markov.h main.cpp)
set_target_properties(MarkovDTMC PROPERTIES LINKER_LANGUAGE CXX)

add_executable(MarkovCTMC markov.cpp markov.h main_ctmc.cpp)
set_target_properties(MarkovCTMC  PROPERTIES LINKER_LANGUAGE CXX)