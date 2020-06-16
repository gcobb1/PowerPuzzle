/*****
Author: Gavin Cobb
Date: April 2020

The purpose of this file is to define the member methods that correspond to the back end that is used to manipulate front end stylings
Puzzle object is the underlying computational model of the display puzzle
*****/

#include "SlidePuzzle.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <Wt/WObject.h>
#include <fstream>


//fills a temporary matrix that corresponds to the current state matrix
void Puzzle::fillSolveTemp(){
	
	this->solveTemp.clear();
	this->solveTemp.resize(this->sizePuz);
	for(int inc50 = 0; inc50 < this->sizePuz; inc50++){
		solveTemp[inc50].resize(this->sizePuz);
	}
	for(int i = 0; i < this->sizePuz; i++){
		for(int j = 0; j < this->sizePuz; j++){
			this->solveTemp[i][j] = this->startGridPuz[i][j];
		}
	}	
}

//function that stores the current amount of correct permutations in counter based on the given state
void Puzzle::checkSolve(){
	this->counter = 0;
	for(int i = 0; i < this->sizePuz; i++){
		for(int j = 0; j < this->sizePuz; j++){
			if(this->startGridPuz[i][j] == this->NEWGRID[i][j]){
				this->counter = this->counter + 1;
			}
		}
	}
		
}

//Creates a new grid where 0 is the final number
void Puzzle::NGFresh(){
	int number1; 
	this->NEWGRID.clear();
	this->NEWGRID.resize(this->sizePuz);
	for(int inc51 = 0; inc51 < this->sizePuz; inc51++){
		NEWGRID[inc51].resize(this->sizePuz);
	}
	for(int i = 0; i < this->sizePuz; i++){
		for(int j = 0; j < this->sizePuz; j++){
			number1 = ((i*this->sizePuz) + j) + 1;
			this->NEWGRID[i][j] = number1;
		}
	}
	this->NEWGRID[(this->sizePuz - 1)][(this->sizePuz - 1)]  = 0;
}

//Creates a fresh temp grid where 0 is final number
void Puzzle::Fresh(){
	int number1; 
	this->freshGrid.clear();
	this->freshGrid.resize(sizePuz);
	for(int inc51 = 0; inc51 < sizePuz; inc51++){
		freshGrid[inc51].resize(sizePuz);
	}
	for(int i = 0; i < this->sizePuz; i++){
		for(int j = 0; j < this->sizePuz; j++){
			number1 = ((i*this->sizePuz)+j) + 1;
			this->freshGrid[i][j] = number1;
		}
	}
	this->freshGrid[(this->sizePuz - 1)][(this->sizePuz - 1)] = 0;
}



// Greedy Pathfinding Algorithm designed to store states of completed columns and rows in order to find an efficient solution to the puzzle at a given state
// The algorithm works by checking the state of permutations of the puzzle, the puzzle solves each position incrementally based on different thresholds that correspond to increasing awareness of approaching the solved state
//Edge Cases are solved by Parity algorithms caught by the program early to ensure short solutions
// This Creates a pathfinding algorithm that finds a solution to the problem extremely quickly, allowing for scalability of thousands of rows and columns, while also finding a solution that is constrained and miniallow for short paths
std::vector<std::vector<int> > Puzzle::slide_puzzle(){
	this->topRowComplete = 0;
	this->sideColComplete = 0;
	this->SwapsForSolveINDEX1D.clear();	
	int flagtwoRedo = 0;
	int someFlag = 0;
	int counterstopInf;
	int randomFlag = 0;
	int flagSlotting1 = 0;	//used to start end of row solver algorithm
	int flagSlotting2 = 0;	//used to start end of side solver algorithm
	int flagSlotting3 = 0;	//used to solve the last 4 numbers in the matrix easily
	int indexNumtoSwap;
	int tempi = 0;		//Values of i and j will always correspond to y and x
	int tempj = 0;
	int counterSide = 0;
	int counterS = 0;
	int indexofTwo;		//index of the value of the last solved state number in first row
	int indexofSev;		//index of the value of the first solved state numver in last row	
	int indexofThr;		//index of number corresponding to size of row
	int indexofFour;	//index of the value of the first solved state number in the second to last row
	int targetIndex = 0;	//index correlating to where the current number being solved needs to be placed before incremented
	std::vector<int>  correctspotsVector;		//vector that stores the state of each number in the grid to check for permutations
	correctspotsVector.resize((this->sizePuz * this->sizePuz));
	int nonnum = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + 1);				//IMPORTANT: corresponds to second number in second to last layer
	int nonnum2 = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + (this->sizePuz - 2));		//IMPORTANT: corresponds to second number in second to last layer

	//main loop that increments through puzzle to solve indexes. Increments are not always linear.
	for(int i = 0; i < (this->sizePuz * this->sizePuz); ++i){

		//index to be solved will now be know as Current Index*
		//if the current index is also the first in a row, except the first, and before the second to last layer, a row has been completed
		if(((i % this->sizePuz) == 0) && (i < nonnum)){
			if(i != 0){
				this->topRowComplete = this->topRowComplete + 1;
				flagSlotting1 = 1;	
			}
		}
		else{
			flagSlotting1 = 0;
		}
		counterSide = 0;
		this->sideColComplete = 0;
		
		//check and add solved states of each index to evaluate next index to solve
		//if the last in a row is solved but second to last is not, both are not solved
		//if the last in the column is solved but second to last is not, both are not solved
		for(int inc100 = 0; inc100 < this->sizePuz; inc100++){
			for(int inc200 = 0; inc200 < this->sizePuz; inc200++){
				if(this->startGridPuz[inc100][inc200] == ((inc100 * this->sizePuz) + inc200) + 1){
					correctspotsVector[((inc100 * this->sizePuz)+inc200)] = (((inc100 * this->sizePuz)+inc200)+1);
					if((inc200 == (this->sizePuz - 1)) && (correctspotsVector[((inc100 * this->sizePuz) + this->sizePuz - 2)] == -1)){
						correctspotsVector[((inc100 * this->sizePuz) + this->sizePuz - 1)] = -1;
					}
					if((inc100 == this->sizePuz - 1) && (inc200 < (nonnum2 % this->sizePuz)) && (correctspotsVector[(nonnum - 1) + inc200] == -1)){
						correctspotsVector[((nonnum + (this->sizePuz - 1)) + inc200)] = -1;
					}
				}
				else{
					correctspotsVector[((inc100 * this->sizePuz)+inc200)] = -1;
					if((inc200 == this->sizePuz - 1) && ((inc100 < (1 + this->topRowComplete)))){
						correctspotsVector[((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))] = -1;
					}
					if((inc100 == this->sizePuz - 1) && (inc200 < (nonnum2 % this->sizePuz))){
						correctspotsVector[((nonnum - 1) + inc200)] = -1;
					}
				}
			}
		}

		//making sure the sides are properly correlated to solved or unsolved pairs
		for(int incrementer001 = 0; incrementer001 < this->sizePuz- 2; incrementer001++){
			if(this->startGridPuz[(this->sizePuz - 1)][incrementer001] != ((((this->sizePuz - 1) * (this->sizePuz)) + incrementer001) + 1)){
				correctspotsVector[(((this->sizePuz - 2) * (this->sizePuz)) + incrementer001)] = -1;
			}
		}

		//finds the number of sides that are completed. If a side is incomplete, all remaining sides are also incomplete	
		counterSide = 0;
		this->sideColComplete = 0;
		for(int increment101 = 0; (increment101 < (this->sizePuz - 2)); increment101++){
			if(correctspotsVector[((this->sizePuz - 2) * this->sizePuz) + increment101] == (nonnum + increment101)){
				if(correctspotsVector[((this->sizePuz - 1) * this->sizePuz) + increment101] == ((nonnum + increment101) + this->sizePuz)){
					counterSide++;
					this->sideColComplete = counterSide;	
				}
				else{
					break;	
				}
			}
			else{
				break;
			}
		}


		//if i is in the 2nd to last layer and greater than nonnum. And the prior side iis not completed then the current index changes to the first unsolved index in last layer
		//if prior side incomplete but the second to last row index is in the correct spot, then flagslotting is skipped and the index will go back to first unsolved of second to last layer
		if((i >= nonnum) && (i < ((this->sizePuz * this->sizePuz) - this->sizePuz))){
			if((this->sideColComplete - (i % this->sizePuz)) != 0){	
				if(correctspotsVector[(((this->sizePuz - 2) * this->sizePuz) + this->sideColComplete)] == -1){
					if(startGridPuz[(this->sizePuz - 2)][this->sideColComplete] == ((((this->sizePuz - 2) * this->sizePuz) + this->sideColComplete) + 1)){
						someFlag = 1;
						randomFlag = 1;
					}
				i = (((this->sizePuz * this->sizePuz) - this->sizePuz) + this->sideColComplete);
				}
			}
		}

		//if current index is in the last row before the last 2 indexes and the sides complete do not correlate to the j index, then they will be completed, so add 1 to sidecomplete.
		if((i > ((nonnum - 1) + this->sizePuz)) && (i < ((nonnum2) + this->sizePuz))){
			if((this->sideColComplete - (i % this->sizePuz)) != 0){
				this->sideColComplete = this->sideColComplete + 1;
				if(i != nonnum2){	
					someFlag = 1;	//someflag is used after every last row number is permuted to allow for flagslotting algorithm and to reset the number to the second to last row.
				}
			}
		}
		
		if(i == ((nonnum + this->sizePuz) + (this->sideColComplete - 1)) && (this->sideColComplete > 0) && (i <= (nonnum2 + this->sizePuz))){// + sideColComplete
			if((someFlag == 1) &&  (randomFlag == 0)){// ((i % this->sizePuz) == 0)){
				flagSlotting2 = 1;	//flagslotting algorithm for side columns will not occur if the second to last row first unsolved is in a solved position but corresponding last layer is not
			}
			else{
				flagSlotting2 = 0;
			}
			if(((i % this->sizePuz) == 1) && (counterS == 0)){
				//counterS++;
				flagSlotting2 = 1;
			}  
		}
		else{		//if not last row do not use algorithm
			flagSlotting2 = 0;	
		}

		//rearrange targets in the end 
		if(i == (((this->sizePuz* this->sizePuz) - 2) - this->sizePuz)){
			i = (this->sizePuz * this->sizePuz) -  3;
		}
		else if(i == (((this->sizePuz* this->sizePuz) - 1) - this->sizePuz)){	
			i = (this->sizePuz * this->sizePuz) -  2;
		}
		else if(i == ((this->sizePuz* this->sizePuz) - 1)){	
			i = (this->sizePuz * this->sizePuz) -  2;
		}
		//the last column will be slotted allowing for final algorithm to solve
		if((i == ((this->sizePuz * this->sizePuz) - 2)) && (randomFlag == 0)){
			flagSlotting2 = 1;	
			flagSlotting3 = 1;	
		}
		else{
			flagSlotting3 = 0;
		}	

		//This block changes the targets from the index they are to the index they need to be in for the algorithms to work
		targetIndex = i;
		if(((targetIndex % this->sizePuz) == (this->sizePuz - 2)) && (i < (nonnum2 - 1))){	//if target is index second to last in row it is now last in row.
			targetIndex = i + 1;
		}
		else if(((targetIndex % this->sizePuz) == (this->sizePuz - 1)) && (i < (nonnum2 - 1))){	//if target is last in row it is now targetted in the next row same column
			targetIndex = targetIndex + this->sizePuz;
		}
		else if((targetIndex == ((nonnum - 1)  + this->sideColComplete)) && (i < nonnum2)){	//if in second to last row target is not in last row
			targetIndex = targetIndex + this->sizePuz;
		}
		else if((targetIndex == (((nonnum + this->sideColComplete) + this->sizePuz) - 1)) && (i < (nonnum2 + this->sizePuz))){	//if in last row but before last 2 columns, target is 1 column to the right
			targetIndex = targetIndex + 1;	
		}


		//this section is for the slotting algoriithms necessary to fiinish rows and columns up for the next increment
		//only occurs if prior is not in correct index and not 0 siince -1 index is impossible
		if(i != 0){
			if(correctspotsVector[i - 1] == -1){
				//algorithm that works by ackowledging the correctness of the prior targetted numbers and permutes them into correct positions, completing a row
				if(flagSlotting1 == 1){	
					flagSlotting1 = 0;
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					tempi = this->indexAti;
					tempj = this->indexAtj;
					if(indexAtj == (this->sizePuz - 1)){
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						for(int inc40 = 0; inc40 < (tempi - (this->topRowComplete - 1)); inc40++){
							this->startGridPuz = this->swapUp();
							if(this->flag == 1){
								this->SwapsForSolveINDEX1D.push_back(2);
								this->flag = 0; //remember to do this flag = 0 for mixUP
							}
						}
						this->startGridPuz = this->swapRight();			
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						this->startGridPuz = this->swapDown();			
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
						this->indexAti	= iIndex0(this->index1D);
						this->indexAtj = jIndex0(this->index1D);
					}
					else if(this->indexAtj == (this->sizePuz - 2)){
						this->startGridPuz = this->swapUp();			
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(2);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						this->startGridPuz = this->swapRight();			
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						this->startGridPuz = this->swapDown();			
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
						this->indexAti	= iIndex0(this->index1D);
						this->indexAtj = jIndex0(this->index1D);
					}
				}
			
				//algorithm that works by ackowledging the correctness of the prior targetted numbers and permutes them into correct positions, completing a column
				if(flagSlotting2 == 1){
					flagSlotting2 = 0;
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					if(indexAti == (this->sizePuz - 1)){
						this->startGridPuz = this->swapUp();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(2);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0; //remember to do this flag = 0 for mixUP
						}
					}
					this->startGridPuz = this->swapLeft();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}

					this->startGridPuz = this->swapDown();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
					this->startGridPuz = this->swapRight();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}

					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
				}
			}
		}
		//before we swap to target indexes for the wraparound in last 2 layers check that both indexes in the column prior are correct with random flag.
		// if they are then the flag was slotted correctly. if not a prior algorithm will change the index to the appropriate row. This fixes edge cases via a backtracking parity algorithm 
		if(someFlag == 1){
			someFlag = 0;
			randomFlag = 0;
			if((i < (nonnum2 + this->sizePuz)) && (randomFlag == 0)){
				i = ((i - this->sizePuz) - 1);
				continue;
			}
		//	else if(randomFlag == 1){
		//		randomFlag = 0;
		//		continue;
		//	}
		}//check
		
		//the following portion checks if the current index is incorrectly permuted.
		//it does this by checking the state of solution of the solved puzzle, as well as taking into account position of current index
		if((correctspotsVector[i] == -1) || (i == (nonnum2 + this->sizePuz))){	//if the item is not placed correctly in the correct spot vector
			
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			tempi = this->indexAti;
			tempj = this->indexAtj;
			//the following type of variables declared as "indexofTwo" and similar styles indicate the stored state positions of variables used to identify edge cases for parity algorithms
			indexofTwo = this->findIndex0((this->sizePuz - 1) + (this->sizePuz * this->topRowComplete));
			indexofThr = this->findIndex0((this->sizePuz + (this->sizePuz * this->topRowComplete)));
			//the if-else statements identify the section in which the index lies as well as solution state of the puzzle to swap the blank space up to the target index of the incremented number
			//this solution takes advantage of the fact that (size of the puzzle -2 / size of the puzzle) indexes are solved in order. thus lowering amount of searchable indexes
			if(((i % this->sizePuz) == (this->sizePuz - 2)) && (i < (nonnum - 1)) && (tempi == (0 + this->topRowComplete))){
				if((indexofTwo == ((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))) && ((indexofThr == ((this->sizePuz - 1) + ((this->topRowComplete + 1) * this->sizePuz))))){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);	//the number pushed back is the direction in which the blank space should move in the front end to solve the puzzle
						this->flag = 0;					//the flag determines the eligibility of the swap based on collision detection of the borders
					}
					continue;
				}
			}
			this->index1D = findIndex0(0);	
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			tempi = this->indexAti;
			tempj = this->indexAtj;
			//to reiterate, these statements determine the section in which the index is stored, and swaps the blank space to that index based on factors such as solved state and location.
			if(((i % this->sizePuz) == (this->sizePuz - 1)) && (i < nonnum - 1) && ((i% this->sizePuz) >= this->indexAtj)){
				for(int inc5 = 0; inc5 < ((1 + this->topRowComplete) - tempi); inc5++){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				for(int inc6 = 0; inc6 < ((targetIndex - (this->topRowComplete * this->sizePuz)) - tempj); inc6++){
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
				}
				//used for edge case when the last to numbers in the index are in swapped position.
				indexofThr = this->findIndex0((this->sizePuz + (this->sizePuz * this->topRowComplete)));
				if(indexofThr == ((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))){		
					this->startGridPuz = this->swapLeft();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
					this->startGridPuz = this->swapUp();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}		
					this->startGridPuz = this->swapRight();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = this->swapDown();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
					this->startGridPuz = this->swapDown();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0; 
					}
					this->startGridPuz = this->swapLeft();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; 
					}
					this->startGridPuz = this->swapUp();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0; 
					}
					this->startGridPuz = this->swapRight();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0; 
					}
					this->startGridPuz = this->swapUp();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = this->swapLeft();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; 
					}
					this->startGridPuz = this->swapDown();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					this->startGridPuz = this->swapRight();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					flagtwoRedo = 1;
				}
			}
			//This if block represents if we are looking for a 1 to swap up
			else if(((i % this->sizePuz) == 0) && (i < (nonnum - 1))){
				for(int inc3 = 0; inc3 < tempj; ++inc3){					 	
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
				}
				for(int inc4 = 0; inc4 < (tempi - this->topRowComplete); inc4++){
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
				}
			}
			else if(((i % this->sizePuz) < (this->sizePuz - 1)) && (i < (nonnum - 1))&& ((i % this->sizePuz) != 0) && ((i % this->sizePuz) >= tempj)){
				for(int inc9 = 0; inc9 < ((targetIndex % this->sizePuz) - tempj); inc9++){
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
				}
				for(int inc11 = 0; inc11 < (tempi - this->topRowComplete); inc11++){
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
				}
			}
			else if(((i % this->sizePuz) < (this->sizePuz - 1)) && (i < (nonnum - 1)) && ((i % this->sizePuz) != 0) && ((i % this->sizePuz)< tempj)){
				for(int inc9 = 0; inc9 < (tempj - (targetIndex % this->sizePuz)); inc9++){
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
				}
				for(int inc11 = 0; inc11 < (tempi - this->topRowComplete); inc11++){
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
				}
			}
			//this is to swap to the number in a column in the second to last row. Contains many edge cases that are easily resolved by moving up or down 1 space, then continuing the algorithm as usual
			else if((i == ((nonnum - 1) + this->sideColComplete)) && (i < nonnum2)){//
				indexofFour = this->findIndex0((nonnum + this->sideColComplete));
				indexofSev = this->findIndex0((nonnum + this->sideColComplete) + this->sizePuz);
				if(indexofSev != ((nonnum + this->sideColComplete) + this->sizePuz)){//stopped here
					if((indexofSev != (((nonnum + this->sideColComplete) + this->sizePuz) - 1)) || (indexofFour != ((nonnum + this->sideColComplete) + this->sizePuz))){
						this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
						this->indexAti	= iIndex0(this->index1D);
						this->indexAtj = jIndex0(this->index1D);
						tempi = this->indexAti;
						tempj = this->indexAtj;
						if(this->indexAti == (this->sizePuz - 1)){
							this->startGridPuz = this->swapUp();
							if(this->flag == 1){
								this->SwapsForSolveINDEX1D.push_back(2);
								this->flag = 0;
							}
						}
						for(int inc12 = 0; inc12 < (tempj - this->sideColComplete); inc12++){
							//ofile << "swappingleft\n";
							this->startGridPuz = this->swapLeft();
							if(this->flag == 1){
								this->SwapsForSolveINDEX1D.push_back(0);
								this->flag = 0;
							}
						}
					}
				}
				for(int inc13 = 0; inc13 < 1; inc13++){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				//another edge case prevention technique
				if(indexofSev == ((nonnum + this->sideColComplete) + this->sizePuz)){
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					tempi = this->indexAti;
					tempj = this->indexAtj;
					//ofile << "Swapping Left for last row i = " << i << " sides  completed = " << this->sideColComplete << "this->sizePuz - 1 - this->sideColComplete = ?\n";
					for(int inc17 = 0; inc17 < (tempj - this->sideColComplete); inc17++){
						//ofile << "swappingleft\n";
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					tempi = this->indexAti;
					tempj = this->indexAtj;
					if((tempj == ((((nonnum + this->sideColComplete) + this->sizePuz) - 1) % this->sizePuz)) && (tempi == (this->sizePuz - 1))){
						this->startGridPuz = this->swapUp();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(2);
							this->flag = 0;
						}
						this->startGridPuz = this->swapRight();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0;
						}
						this->startGridPuz = this->swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
				}
				//another edge case prevention technique in the last 2 layers.
				//to explain further an edge case in the last 2 layers is defined by a swapping of the indexes that are in the same column, or an inevitability of that occuring by normal means
				else if((indexofSev == (((nonnum + this->sideColComplete) + this->sizePuz) - 1)) && (indexofFour == ((nonnum + this->sideColComplete) + this->sizePuz))){
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					tempi = this->indexAti;
					tempj = this->indexAtj;
					//ofile << "Swapping Left for last row i = " << i << " sides  completed = " << this->sideColComplete << "this->sizePuz - 1 - this->sideColComplete = ?\n";	
					for(int inc90 = 0; inc90 < (tempj - this->sideColComplete); inc90++){
						//ofile << "swappingleft\n";
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
				}
//might need stuff here
				//another edge case prevention technique
				if((indexofSev == (((nonnum + this->sideColComplete) + this->sizePuz) - 1)) && (indexofFour == ((nonnum + this->sideColComplete) + this->sizePuz))){
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
				}
				indexofSev = this->findIndex0(((nonnum + this->sideColComplete) + this->sizePuz));
				indexofFour = this->findIndex0((nonnum + this->sideColComplete));
				if((indexofSev == (nonnum + this->sideColComplete)) && (indexofFour == ((nonnum + this->sideColComplete) - 1))){
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					continue;
				}
				else if((indexofSev == ((nonnum + this->sideColComplete) - 1)) && (indexofFour == ((nonnum + this->sideColComplete) + this->sizePuz))){
					this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
					this->indexAti	= iIndex0(this->index1D);
					this->indexAtj = jIndex0(this->index1D);
					tempi = this->indexAti;
					tempj = this->indexAtj;
					if((tempj == ((((nonnum + this->sideColComplete) - 1) + this->sizePuz) % this->sizePuz)) && (tempi == (this->sizePuz - 1))){

						this->startGridPuz = this->swapUp();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(2);
							this->flag = 0;
						}
						this->startGridPuz = this->swapRight();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0;
						}
						this->startGridPuz = this->swapRight();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0;
						}
						this->startGridPuz = this->swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
						this->startGridPuz = this->swapUp();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(2);
							this->flag = 0;
						}
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
						this->startGridPuz = this->swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
					}
				}
			}
			//this is for swapping to indexes of number in the last row
			else if((i == (((nonnum + this->sideColComplete) + this->sizePuz) - 1)) && (i < (nonnum2 + this->sizePuz))){
				this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
				this->indexAti	= iIndex0(this->index1D);
				this->indexAtj = jIndex0(this->index1D);
				if(this->indexAti == (this->sizePuz - 2)){
					
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
				this->indexAti	= iIndex0(this->index1D);
				this->indexAtj = jIndex0(this->index1D);
				tempi = this->indexAti;
				tempj = this->indexAtj;
				if(i < this->indexAtj - 1){
					for(int incrementer102 = i; incrementer102 < (tempj - 1); i++){
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
					//do something like swap left and down or something
				}
			}//
			//a special case only for the second to last index
			else if(i == (nonnum2 + this->sizePuz)){
				if(this->indexAti == (this->sizePuz - 2)){	
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				if(this->indexAtj == (this->sizePuz - 1)){
				
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
				}
			}
			this->index1D = findIndex0(0);
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			tempi = this->indexAti;
			tempj = this->indexAtj;
			//special edge case that completes a row in 1 move, created for efficiency
			indexofTwo = this->findIndex0((this->sizePuz - 1) + (this->sizePuz * this->topRowComplete));
			indexofThr = this->findIndex0((this->sizePuz + (this->sizePuz * this->topRowComplete)));
			if(((i % this->sizePuz) == (this->sizePuz - 2)) && (i < nonnum - 1) && (tempi == (0 + this->topRowComplete))){
				if((indexofTwo == ((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))) && ((indexofThr == ((this->sizePuz - 1) + ((this->topRowComplete + 1) * this->sizePuz))))){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					continue;
				}
			}
			


			//Now that the blank space is in the spot where the next number to be solved needs to be, we use a greedy search pathfinding algorithm to swap to the location of the number to be solved
			indexNumtoSwap = this->findIndex0(i + 1);
			this->indexNumi = this->iIndex0(indexNumtoSwap);
			this->indexNumj = this->jIndex0(indexNumtoSwap);
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			//the function that swaps
			this->startGridPuz = this->swapFrom0toNum(this->index1D, indexNumtoSwap);
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d	
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			indexNumtoSwap = this->findIndex0(i + 1);
			this->indexNumi = this->iIndex0(indexNumtoSwap);
			this->indexNumj = this->jIndex0(indexNumtoSwap);


			//final algorithm that swaps the second to last number into the correct place, solving the 2 last indexes in the last 2 rows at the same time.
			if(flagSlotting3 == 1){
				if(this->indexAtj == (this->sizePuz - 2)){
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				else if(this->indexAtj == (this->sizePuz - 1)){
					if(this->indexAti == (this->sizePuz - 2)){
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
						this->startGridPuz = this->swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
						this->startGridPuz = this->swapRight();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0;
						}
					}
				}
				//When this returns, the puzzle solves.
				return this->startGridPuz;
			}

			if(flag == 7){
				return this->startGridPuz;
			}
			
			//The final part to solve each index incrementally relying on the state of the solution is the function that wraps the blank space around the number to manipulate it into the solved state
			//wraparound
			//1 function is called per increment depending on the section in which the current index is located in the main loop
			if(((i % this->sizePuz) == 0) && (i < (nonnum - 1))){
				this->startGridPuz = this->wrapAround(i, targetIndex, this->index1D, indexNumtoSwap);
			
			}
			else if(((i % this->sizePuz) < (this->sizePuz - 1)) && (i < nonnum - 1) && ((i % this->sizePuz) != 0)){
				this->startGridPuz = this->wrapAround(i, targetIndex, this->index1D, indexNumtoSwap);
			}
			else if((i  % this->sizePuz) == (this->sizePuz - 1)){
				this->startGridPuz = this->wrapAround(i, targetIndex, this->index1D, indexNumtoSwap);
				flagSlotting1 = 1;
			}
			else if((i >= (nonnum - 1)) && (i < nonnum2)){
				this->startGridPuz = this->wrapAround(i, targetIndex, this->index1D, indexNumtoSwap);
			}
			else if((i >= ((nonnum - 1) + this->sizePuz)) && (i < ((this->sizePuz * this->sizePuz) - 2))){
				this->startGridPuz = this->wrapAround(i, targetIndex, this->index1D, indexNumtoSwap);
			}
		}
	}
	//this return should never be called, however it is used in case of unforeseen circumstances	
	return this->startGridPuz;
}


//function that finds size x 6 random numbers and uses these to hash directions into a vector that are used to mix up the matrix
std::vector<std::vector<int> > Puzzle::mixUp(){
	
	this->SwapsForMixUpINDEX1D.clear();	
	int secretNum;
	this->randVals.clear();
	srand(time(NULL));
	//getrandom numbers
	for(int ii = 0; ii < ((this->sizePuz * this->sizePuz) * 6) ; ii++){
		secretNum = 0 + rand() % ((3+1)-0);
		this->randVals.push_back(secretNum);
	}
	int j = 0;
	for(int i = 0; i < this->randVals.size(); i++){
		if((i%4) == 0){	//hash these numbers into directions with modulo
			for(j = 0; j < this->randVals[i]; j++){
				//use directions to mix	
				this->startGridPuz = this->swapLeft();
				SwapsForMixUpINDEX1D.push_back(0);
			}
		}
		else if((i%4) == 1){
			for(j = 0; j < this->randVals[i]; j++){
				this->startGridPuz = this->swapUp();
				SwapsForMixUpINDEX1D.push_back(1);
			}
		}
		else if((i%4) == 2){
			for(j = 0; j < this->randVals[i]; j++){
				this->startGridPuz = this->swapRight();
				SwapsForMixUpINDEX1D.push_back(2);
			}
		}
		else if((i%4) == 3){
			for(j = 0; j < this->randVals[i]; j++){
				this->startGridPuz = this->swapDown();
				SwapsForMixUpINDEX1D.push_back(3);
			}
		}
	}
	return this->startGridPuz;
}

//finds the index of the number in parameter in 1 dimension
int Puzzle::findIndex0(int num){

	int calculations;
	for(int i = 0; i < this->sizePuz; i++){
		for(int j = 0; j < this->sizePuz; j++){
			if(this->startGridPuz[i][j] == num){
				calculations = (i*this->sizePuz) + j;
			}
		}
	}
	return calculations;	//Index of 0 in 1D
}
//finds the index of j in 2 dimensions
int Puzzle::jIndex0(int index0){
	int indexOfjAt0 = index0 % this->sizePuz;
	return indexOfjAt0;
}
//finds the index of i in 2 dimensions
int Puzzle::iIndex0(int index0){
	
	int indexOfjAt0 = index0 % this->sizePuz;
	int indexOfiAt0 = ((index0 - indexOfjAt0) / this->sizePuz);
	return indexOfiAt0;
}

//function that swaps the blank space with the number that is to the right of the blank space
std::vector<std::vector<int> > Puzzle::swapRight(){
	
	std::vector<std::vector<int> > resulter;
	this->index1D = findIndex0(0);
	this->indexAti = iIndex0(this->index1D);
	this->indexAtj = jIndex0(this->index1D);
	resulter = this->startGridPuz;
	//checks for collision of edge before swapping
	if(indexAtj == (this->sizePuz-1)){
		return resulter;
	}
	//copies are used and can be replaced in future versions
	resulter[indexAti][indexAtj] = resulter[indexAti][indexAtj+1];
	resulter[indexAti][indexAtj+1] = 0;
	this->numMoves++;
	this->flag = 1;

	return resulter;
}
//same as above
std::vector<std::vector<int> > Puzzle::swapLeft(){

	std::vector<std::vector<int> > resulter;
	this->index1D = findIndex0(0);
	this->indexAti = iIndex0(this->index1D);
	this->indexAtj = jIndex0(this->index1D);
	resulter = this->startGridPuz;
	if(indexAtj == (0)){
		return resulter;
	}
	resulter[indexAti][indexAtj] = resulter[indexAti][indexAtj-1];
	resulter[indexAti][indexAtj-1] = 0;
	this->numMoves++;
	this->flag = 1;
	return resulter;
}
//same as above
std::vector<std::vector<int> > Puzzle::swapUp(){
	
	std::vector<std::vector<int> > resulter;
	this->index1D = findIndex0(0);
	this->indexAti = iIndex0(this->index1D);
	this->indexAtj = jIndex0(this->index1D);
	resulter = this->startGridPuz;
	if(indexAti == (0)){
		return resulter;
	}
	resulter[indexAti][indexAtj] = resulter[indexAti-1][indexAtj];
	resulter[indexAti-1][indexAtj] = 0;
	this->numMoves++;
	this->flag = 1;

	return resulter;
}
//same as above
std::vector<std::vector<int> > Puzzle::swapDown(){

	std::vector<std::vector<int> > resulter;
	this->index1D = findIndex0(0);
	this->indexAti = iIndex0(this->index1D);
	this->indexAtj = jIndex0(this->index1D);
	resulter = this->startGridPuz;
	if(this->indexAti == (this->sizePuz - 1)){
		return resulter;
	}
	resulter[indexAti][indexAtj] = resulter[indexAti+1][indexAtj];
	resulter[indexAti+1][indexAtj] = 0;
	this->numMoves++;
	this->flag = 1;
	
	return resulter;
}


//greedy search algorithm that interprets the section in which the current index is located, and the vector distance of this index to the number that should be permuted there.
//the blank space is always located in the position the current index target needs to be placed thus making it easy to swap.
//since the lower portions are unsolved when the top is unsolved, and the puzzle is solved incrementally, the blanks often swap down and to the right or left until the current number is swapped
std::vector<std::vector<int> > Puzzle::swapFrom0toNum(int Index1D0, int Index1Dnum){
	
	int nonnum = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + 1);
	int nonnum2 = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + (this->sizePuz - 2));
	this->indexAti = this->iIndex0(Index1D0);
	this->indexAtj = this->jIndex0(Index1D0);
	this->indexNumi = this->iIndex0(Index1Dnum);
	this->indexNumj = this->jIndex0(Index1Dnum);
	int flagforSev = 0;

	//This is an edge case for the first number in the last to rows
	if(this->startGridPuz[this->indexNumi][this->indexNumj] == ((nonnum - 1) + this->sizePuz)){
		flagforSev = 1;
	}
	int inc20 = this->indexAtj;
	int inc200 = this->indexNumj;
	int incSwap;
	//if the j index of the target is larger than swap right because those to the right are unsolved compared to the left
	if(inc20 < this->indexNumj ){
		for(inc20 = this->indexAtj; inc20 < inc200; inc20++){
			this->startGridPuz = this->swapRight();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(1);
				this->flag = 0;
			}
		}
	}
	this->indexAti = this->iIndex0(Index1D0);
	this->indexAtj = this->jIndex0(Index1D0);
	this->indexNumi = this->iIndex0(Index1Dnum);
	this->indexNumj = this->jIndex0(Index1Dnum);
	int inc210 = this->indexAti;
	int inc2100 = this->indexNumi;
	//swap down before swapping left if the target j index is lower
	//swap down first because all lower indexes are technically unsolved
	if(inc210 != (this->sizePuz - 1)){
		for(int inc21 = this->indexAti; inc21 < inc2100; inc21++){
			this->startGridPuz = swapDown();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(3);
				this->flag = 0;
			}
		}
	}
	else{
		this->indexAti = this->iIndex0(Index1D0);
		this->indexAtj = this->jIndex0(Index1D0);
		this->indexNumi = this->iIndex0(Index1Dnum);
		this->indexNumj = this->jIndex0(Index1Dnum);
		int inc210i = this->indexAti;
		int inc2100i = this->indexNumi;
		for(int inc22 = inc210i; inc22 > inc2100i; inc22--){
			this->startGridPuz = swapUp();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(2);
				this->flag = 0;
			}
		}
	}
	this->indexAti = this->iIndex0(Index1D0);
	this->indexAtj = this->jIndex0(Index1D0);
	this->indexNumi = this->iIndex0(Index1Dnum);
	this->indexNumj = this->jIndex0(Index1Dnum);
	int inc210jj = this->indexAtj;
	int inc2100jj = this->indexNumj;
	//lastly swap left, the most dangerous swap since those to the left are solved.
	incSwap = this->indexAtj;
	if(incSwap >= this->indexNumj){
		for(incSwap = inc210jj; incSwap > inc2100jj; incSwap--){
			this->startGridPuz = this->swapLeft();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(0);
				this->flag = 0;
			}
		}
	}
	return this->startGridPuz;
}


//This is the most vital function for solving the index.
//It fully utilizes the state of the puzzle, more specifically, it checks the solved permutations and the indexes in which the blank and target lie, which are always adjacent.
//The functions then manipulates these numbers by swapping around the target number while avoiding solved indexes. 
//it does this in a loop that contains smaller algorithms that define the state and section of the puzzle to manipulate this data in.
//for example the algorithm will find that the blank space is to the left of the number that is the target for the current index, it will then proceed to put it under the target and perform an algorithm depending on the
//position in correlation to the currentindex/targetindex. However, this can be performed in any direction and in much more complex scenarios.
//all edge cases are taken care of before the swaptonum so there is no worry for an infinite loop
std::vector<std::vector<int> > Puzzle::wrapAround(int increment, int targetIndex, int Index1D0,
                                          int Index1Dnum){
	int nonnum = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + 1);
	int nonnum2 = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + (this->sizePuz - 2));

	int index1DNUM = Index1Dnum;
	int INDEX1D0 = Index1D0;
	int targetIndexi = this->iIndex0(targetIndex);
	int targetIndexj = this->jIndex0(targetIndex);
	this->indexAti = this->iIndex0(Index1D0);
	this->indexAtj = this->jIndex0(Index1D0);
	this->indexNumi = iIndex0(Index1Dnum);
	this->indexNumj = jIndex0(Index1Dnum);
	int targetNum = this->startGridPuz[indexNumi][indexNumj];
	int ir = increment;
	int count = 0;
	//main loop that checks for solved state of the index in question
	while(this->startGridPuz[targetIndexi][targetIndexj] != targetNum){
		count++;
		index1DNUM = this->findIndex0(targetNum);
		INDEX1D0 = this->findIndex0(0);
		this->indexAti = this->iIndex0(INDEX1D0);
		this->indexAtj = this->jIndex0(INDEX1D0);
		this->indexNumi = this->iIndex0(index1DNUM);
		this->indexNumj = this->jIndex0(index1DNUM);
		//these break statements are placed all over to confirm the solved state of the index
		if(this->startGridPuz[targetIndexi][targetIndexj] == targetNum){
			break;
		}
		//just in case for no infinite loops
		if(count == 30){
			return this->startGridPuz;//for error but may not scale to large systems
		}
		//the Remaining if else statements check the section in which the current index is located as well as the adjacency factor to the target index number location
		if(((ir % this->sizePuz) == 0) && (ir < nonnum - 1) && (this->indexAtj != this->indexNumj-1) && (this->indexAtj != this->indexNumj+1)){
			//These algorithms basically swap around the targetted index to more favored positions while also efficinetly and cleanly solving in many different permutations.
			if(this->indexNumi == (0 + this->topRowComplete)){
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				index1DNUM = this->findIndex0(targetNum);
				INDEX1D0 = this->findIndex0(0);
				this->indexAti = this->iIndex0(INDEX1D0);
				this->indexAtj = this->jIndex0(INDEX1D0);
				this->indexNumi = this->iIndex0(index1DNUM);
				this->indexNumj = this->jIndex0(index1DNUM);
				if(this->indexNumj == (this->sizePuz - 1)){
					this->startGridPuz = swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					this->startGridPuz = swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					index1DNUM = this->findIndex0(targetNum);
					INDEX1D0 = this->findIndex0(0);
					this->indexAti = this->iIndex0(INDEX1D0);
					this->indexAtj = this->jIndex0(INDEX1D0);
					this->indexNumi = this->iIndex0(index1DNUM);
					this->indexNumj = this->jIndex0(index1DNUM);
				}
			}
			else if((this->indexNumi < (this->sizePuz - 1))  && (this->indexNumj != (this->sizePuz - 1))){
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				index1DNUM = this->findIndex0(targetNum);
				INDEX1D0 = this->findIndex0(0);
				this->indexAti = this->iIndex0(INDEX1D0);
				this->indexAtj = this->jIndex0(INDEX1D0);
				this->indexNumi = this->iIndex0(index1DNUM);
				this->indexNumj = this->jIndex0(index1DNUM);
			}//save next line for later probably < sizePuz - 2 though
			else if((this->indexNumi < (this->sizePuz - 1)) && (this->indexNumj == (this->sizePuz - 1))){
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				index1DNUM = this->findIndex0(targetNum);
				INDEX1D0 = this->findIndex0(0);
				this->indexAti = this->iIndex0(INDEX1D0);
				this->indexAtj = this->jIndex0(INDEX1D0);
				this->indexNumi = this->iIndex0(index1DNUM);
				this->indexNumj = this->jIndex0(index1DNUM);
			}
		}//
		else if(((ir % this->sizePuz)== 0) && (ir < (nonnum - 1)) && (this->indexAtj == this->indexNumj+1)){
			 
			this->startGridPuz = swapDown();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(3);
				this->flag = 0;
			}
			this->startGridPuz = swapLeft();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(0);
				this->flag = 0;
			}
			this->startGridPuz = swapLeft();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(0);
				this->flag = 0;
			}
			this->startGridPuz = swapUp();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(2);
				this->flag = 0;
			}
				
			this->startGridPuz = swapRight();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(1);
				this->flag = 0;
			}
			index1DNUM = this->findIndex0(targetNum);
			INDEX1D0 = this->findIndex0(0);
			this->indexAti = this->iIndex0(INDEX1D0);
			this->indexAtj = this->jIndex0(INDEX1D0);
			this->indexNumi = this->iIndex0(index1DNUM);
			this->indexNumj = this->jIndex0(index1DNUM);
		}//
		else if(((ir % this->sizePuz) < (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj == this->indexNumj - 1) && ((ir % this->sizePuz)!= 0)){// && (this->indexAti < (this->sizePuz - 1))){
			if(this->indexNumj < (this->sizePuz - 1)){//may have problem here
				if(this->indexAti < (this->sizePuz - 1)){
					this->startGridPuz = swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					this->startGridPuz = swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					if(indexNumj < targetIndexj){
						this->startGridPuz = swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
					else{
						this->startGridPuz = swapUp();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(2);
							this->flag = 0;
						}
						this->startGridPuz = swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
						this->startGridPuz = swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
					}
				}
				else{
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					if( indexNumj >= targetIndexj){
						this->startGridPuz = swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
					}		
					else{
						
						this->startGridPuz = swapRight();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(1);
							this->flag = 0;
						}
						this->startGridPuz = swapDown();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(3);
							this->flag = 0;
						}
						this->startGridPuz = swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}				
				}
			}	
		}
		else if(((ir % this->sizePuz) < (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj != this->indexNumj + 1) && (this->indexAtj != this->indexNumj - 1) && ((ir % this->sizePuz) != 0)){
			if(this->indexNumi == (0 + this->topRowComplete)){
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
			}
			else{
				if(this->indexAtj < (this->sizePuz - 1)){
					this->startGridPuz = swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}	
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				else{
					this->startGridPuz = swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}	
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
					this->startGridPuz = swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}	
			}
		}//here//version 1.1
		else if(((ir  % this->sizePuz) < (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj == this->indexNumj + 1) && ((ir % this->sizePuz) != 0)){
			if(this->indexNumi == (this->sizePuz - 1)){//may have problem here
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
			}
			else{
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
			}
		}
		//here	

		else if(((ir % this->sizePuz) == (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj != this->indexNumj - 1) && (this->indexAtj != this->indexNumj + 1)){
			if(indexNumj == (this->sizePuz - 1)){
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
			}
			else{
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				if(indexNumj < targetIndexj){
					this->startGridPuz = swapLeft();
					if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
					}
				}
				else{
					this->startGridPuz = swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
					this->startGridPuz = swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
					this->startGridPuz = swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
			}
			//	if(indexNumj < targetIndexj){
			
			index1DNUM = this->findIndex0(targetNum);
			INDEX1D0 = this->findIndex0(0);
			this->indexAti = this->iIndex0(INDEX1D0);
			this->indexAtj = this->jIndex0(INDEX1D0);
			this->indexNumi = this->iIndex0(index1DNUM);
			this->indexNumj = this->jIndex0(index1DNUM);
		}//
		else if(((ir  % this->sizePuz) == (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti < (this->sizePuz - 1))){
			if(this->indexNumj < (this->sizePuz - 1)){
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
			}
			else{
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
			}
		}
		else if(((ir % this->sizePuz) == (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti == (this->sizePuz - 1))){
			if(this->indexNumj < (this->sizePuz - 1)){
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
			}
			else{
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
			}
		}
		else if(((ir % this->sizePuz) == (this->sizePuz - 1)) && (ir < nonnum - 1) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti == (this->sizePuz - 1))){
			if(this->indexNumj < (this->sizePuz - 1)){
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
			}
			else if(this->indexNumj == (this->sizePuz - 1)){ 
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
			}
		}//
		else if(((ir % this->sizePuz) == (this->sizePuz - 1)) && (ir < nonnum - 1) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti < (this->sizePuz - 1))){
			
			if(this->indexNumj < (this->sizePuz - 1)){
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
			}
			else if(this->indexNumj == (this->sizePuz - 1)){ 
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
			}	
		}
		else if(((ir % this->sizePuz) == (this->sizePuz - 1)) && (ir < nonnum - 1) && (this->indexAtj != (this->indexNumj - 1))){
			this->startGridPuz = swapLeft();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(0);
				this->flag = 0;
			}
			this->startGridPuz = swapUp();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(2);
				this->flag = 0;
			}
			this->startGridPuz = swapUp();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(2);
				this->flag = 0;
			}
			this->startGridPuz = swapRight();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(1);
				this->flag = 0;
			}
			this->startGridPuz = swapDown();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(3);
				this->flag = 0;
			}
		}
	
		else if(ir == ((nonnum - 1) + this->sideColComplete)){
			if(this->indexAti == (this->sizePuz - 2)){	
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
			}
			index1DNUM = this->findIndex0(targetNum);
			INDEX1D0 = this->findIndex0(0);
			this->indexAti = this->iIndex0(INDEX1D0);
			this->indexAtj = this->jIndex0(INDEX1D0);
			this->indexNumi = this->iIndex0(index1DNUM);
			this->indexNumj = this->jIndex0(index1DNUM);
			if(this->startGridPuz[targetIndexi][targetIndexj] == targetNum){
				break;
			}

				if(this->indexAtj > 1){
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}

			}
		}//finsihed
		else if(ir == (((nonnum - 1) + this->sideColComplete) + this->sizePuz)){//if this inovlves nonnum2 then must create another for all bottom row 
			if(this->indexAti != this->indexNumi){
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}
				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
			}
			else if((indexAtj > indexNumj) && (indexAti == indexNumi)){
				this->startGridPuz = swapUp();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(2);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapLeft();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(0);
					this->flag = 0;
				}
				this->startGridPuz = swapDown();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(3);
					this->flag = 0;
				}

				this->startGridPuz = swapRight();
				if(this->flag == 1){
					this->SwapsForSolveINDEX1D.push_back(1);
					this->flag = 0;
				}
			}
		}
	}	
	return this->startGridPuz;
}
