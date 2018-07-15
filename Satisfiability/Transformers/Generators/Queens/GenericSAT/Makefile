# Oliver Kullmann, 6.7.2018 (Swansea)

SHELL = /bin/bash
.SUFFIXES :

.PHONY : all clean

CXX = g++

Standard_options = --std=c++11 -pedantic
Warning_options = -Wall
Optimisation_options = -Ofast -DNDEBUG
Optimisation_options_full = -Ofast -DNDEBUG
Debug_options = -g

all : program program_debug

program : Program.cpp Backtracking.hpp ChessBoard.hpp NQueens.hpp NQueensPartial.hpp
	$(CXX) $(Standard_options) $(Warning_options) -Wno-parentheses $(Optimisation_options) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

program_debug : Program.cpp Backtracking.hpp ChessBoard.hpp NQueens.hpp NQueensPartial.hpp
	$(CXX) $(Standard_options) $(Warning_options) -Wno-parentheses $(Debug_options) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean :
	- rm program program_debug