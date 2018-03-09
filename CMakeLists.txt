### Garrett Jennings A01491831	
cmake_minimum_required (VERSION 3.0)
project (Shell)

if (CMAKE_COMPLIER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -Wall -Wextra -g3 ${CMAKE_CXX_FLAGS}")
endif()

add_executable(Shell main.cpp func.hpp func.cpp)
