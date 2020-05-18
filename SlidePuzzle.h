#ifndef SLIDE_PUZZLE_H
#define SLIDE_PUZZLE_H
#include <string>
#include <vector>
#include <cstdlib>
#include <Wt/WObject.h>
#include <fstream>
//Puzzle object that is the underlying computational model of the display puzzle
class Puzzle : public Wt::WObject
{
public:
	std::vector<std::vector<int> > freshGrid;
	std::vector<int> randVals;
	std::vector<int> SwapsForMixUpINDEX1D;
	std::vector<std::vector<int> > solveTemp;	
	std::vector<int> SwapsForSolveINDEX1D;
	std::vector<int> temporaryVect;
	std::vector<std::vector<int> > solvedMatrix;
        std::vector<std::vector<int> > startGridPuz; //Represent Puzzle Grid
        std::vector<int> startRowPuz; //puzzle row
	int sizePuz = 3;	//num rows
	int elementnumPuz;	//index of number in 2D Vector in 1D
	int numMoves = 0;	
	int index1D;	//index of 0 in 1D
	int indexAti;	//index of 0 in i, and j is below
	int topRowComplete = 0;	
	int SideColumnComplete = 0;
	int indexAtj;
	int indexNumi;
	int indexNumj;
	int counter = 0;
	int flag = 0;
	int locationof0MIX = 0;
	int mixINDEXi = 0;
	int solveINDEXi = 0;
	int mixINDEXj = 0;
	int solveINDEXj = 0;
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
	~Puzzle(){
		delete this;
	}
	std::vector<std::vector<int> > NEWGRID = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
	void NGFresh();
	void Fresh();	
	//Solves Puzzle From mixed state (below)
	std::vector<std::vector<int> > slide_puzzle();
	//Mixes Puzzle with random swaps	
	std::vector<std::vector<int> > mixUp();
	void printDoubleVec(std::vector<std::vector<int> > doubVec);
	//finds Index of 0 in 1D
	int findIndex0(int num);
	int rowSize(std::vector<std::vector<int> > doubleVVEc);
	//finds index of column that 0 resides
	int jIndex0(int index0);
	//finds index of row that 0 resides
	int iIndex0(int index0);
	std::vector<std::vector<int> > swapRight();
	std::vector<std::vector<int> > swapUp();
	std::vector<std::vector<int> > swapLeft();
	std::vector<std::vector<int > > swapDown();
	//Swaps indexes from the value 0 to the next number that needs to be placed
	std::vector<std::vector<int> > swapFrom0toNum(int Index1D0, int Index1Dnum);
	//Main Algorithm that takes into account position and solves the targetted number based on layer1
	std::vector<std::vector<int> > wrapAround(int increment, int targetIndex, int Index1D0,
						   int Index1Dnum);
	void printVec(std::vector<std::vector<int> > &valsVec);
	void fillSolveTemp();
	void checkSolve();
};
#endif
