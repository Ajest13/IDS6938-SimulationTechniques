cmake_minimum_required(VERSION 2.8.9)

project (Queues)


include_directories( 
   ${CMAKE_CURRENT_SOURCE_DIR}/../../lecture9/external/eigen
)

add_executable(MM1 main.cpp mm1_queue.cpp mm1_queue.h random_number_generator.h customer.h)
set_target_properties(MM1 PROPERTIES LINKER_LANGUAGE CXX)