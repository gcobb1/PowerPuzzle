#ifndef SLIDE_PUZZLE_H
#define SLIDE_PUZZLE_H

/*****
Author: Gavin Cobb
Date: April 2020

The Purpose of this file is to store the class and member function declarations for the backend that creates manipulations for the frontend to correlate to
*****/




#include <string>
#include <vector>
#include <cstdlib>
#include <Wt/WObject.h>
#include <fstream>

//Puzzle object that is the underlying computational model of the displayed puzzle
class Puzzle : public Wt::WObject
{
public:
	std::vector<std::vector<int> > freshGrid;	//ordered new 2d Vector
	std::vector<int> randVals;			//contains random values for the mixing function to hash out
	std::vector<int> SwapsForMixUpINDEX1D;		//contains values that correspond to directions hashed from the random numbers
	std::vector<std::vector<int> > solveTemp;	//vector of solved puzzle
	std::vector<int> SwapsForSolveINDEX1D;		//contains values that correspond to directions made from solution function
	std::vector<int> temporaryVect;			
	std::vector<std::vector<int> > solvedMatrix;	
        std::vector<std::vector<int> > startGridPuz; 	//Represent Puzzle Grid in the current state
        std::vector<int> startRowPuz; 			//puzzle row
	int sizePuz = 3;				//num rows
	int elementnumPuz;				//index of number in 2D Vector in 1D
	int numMoves = 0;	
	int index1D;					//index of 0 in 1D
	int indexAti;					//index of 0 in i, and j is below
	int topRowComplete = 0;				//amount of rows completed (stores state)
	int sideColComplete = 0;			//amount of columns completed (stores state)
	int indexAtj;
	int indexNumi;
	int indexNumj;
	int counter = 0;
	int flag = 0;					//flag that stores the success of a swap depending on position of the blank
	int locationof0MIX = 0;				//loc of 0 after the mixup function
	int mixINDEXi = 0;				//corresponding indexes
	int solveINDEXi = 0;
	int mixINDEXj = 2;
	int solveINDEXj = 2;

	//puzzle default constructor that adds in the initial state of the puzzle which is starting at +10 to begin
	Puzzle(){
		for(int i = 0; i < sizePuz; i++){
			for(int j = 0; j < sizePuz; j++){
				elementnumPuz = (i*sizePuz)+j;
				startRowPuz.push_back(elementnumPuz);
			}
			startGridPuz.push_back(startRowPuz);
			startRowPuz.clear();
		}
	}	
	
	std::vector<std::vector<int> > NEWGRID = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};	//a solved grid
	void NGFresh();						//resets current grid to fresh grids
	void Fresh();	
	std::vector<std::vector<int> > slide_puzzle();		//Solves Puzzle From mixed state (below)
	std::vector<std::vector<int> > mixUp();			//Mixes Puzzle with random swaps	
	void printDoubleVec(std::vector<std::vector<int> > doubVec);
	int findIndex0(int num);				//finds Index of 0 in 1D
	int rowSize(std::vector<std::vector<int> > doubleVVEc);
	int jIndex0(int index0);				//finds index of column that 0 resides
	int iIndex0(int index0);				//finds index of row that 0 resides
	std::vector<std::vector<int> > swapRight();
	std::vector<std::vector<int> > swapUp();
	std::vector<std::vector<int> > swapLeft();
	std::vector<std::vector<int > > swapDown();
	std::vector<std::vector<int> > swapFrom0toNum(int Index1D0, int Index1Dnum);	//Swaps indexes from the value 0 to the next number that needs to be placed
	std::vector<std::vector<int> > wrapAround(int increment, int targetIndex, int Index1D0, int Index1Dnum);	//Main Algorithm that takes into account position and solves the targetted number on layer
	void printVec(std::vector<std::vector<int> > &valsVec);
	void fillSolveTemp();
	void checkSolve();
};
#endif
