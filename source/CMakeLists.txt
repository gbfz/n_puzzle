cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project (n_puzzle)
add_compile_options(-g -Wall -Wextra -Wpedantic -Wno-implicit-fallthrough)

add_executable(test
	Grid.cpp
	coords.cpp
	SnailFill.cpp
	NPuzzle.cpp
	test.cpp
)
