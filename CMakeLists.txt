# CMakeList.txt : CMake project for Skaiciutuvas, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Skaiciutuvas")

# Add source to this project's executable.
add_executable (Skaiciutuvas
	"main.cpp"
	"main.hpp"
	"EilAnalizator.hpp"
	"EilAnalizator.cpp")

# TODO: Add tests and install targets if needed.
