cmake_minimum_required(VERSION 2.8.9)

project (Discrete2)

add_executable(Random random.cpp)
add_executable(QuasiRandom-Sobolo quasi.cpp sobol.cpp sobol.hpp)
add_executable(DiceRoll dice.cpp)