/******************
Author: Gavin Cobb
Title: SlidePuzzleAlgorithmicVisualizer
Alternate Title: Power Puzzle!
Version 1.0
Date: 14 April 2020
Description: Sliding Puzzle Visualizer written in C++, Wt framework, and Css that uses algorithms to solve a Slide Puzzle from mixed positions. 
	     also allows the user to Mix the puzzle at random from a solved state, Attempt to solve the mixed puzzle, Get hints at next locations 
	     to try to solve for, Displays Move counts, Displays Moves done, Displays timer, and displays a high score of lowest amount of moves to solve
	     The algorithms used to solve utilize AI hill climb search.
*****************/
#include <Wt/WApplication.h>
#include "SlidePuzzle.h"
#include "WtEnvironment.h"

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
    	return std::make_unique<tableApplication>(env);
    });
}
