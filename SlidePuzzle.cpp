#include "SlidePuzzle.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <Wt/WObject.h>
//Puzzle object that is the underlying computational model of the display puzzle

//Puzzle Class Public Method Defs..
void Puzzle::fillSolveTemp(){
	
	this->solveTemp.clear();
	this->solveTemp.resize(3);
	for(int inc50 = 0; inc50 < 3; inc50++){
		solveTemp[inc50].resize(3);
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			this->solveTemp[i][j] = this->startGridPuz[i][j];
		}
	}	
}

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

void Puzzle::Fresh(){
	int number1; 
	this->freshGrid.clear();
	this->freshGrid.resize(3);
	for(int inc51 = 0; inc51 < 3; inc51++){
		freshGrid[inc51].resize(3);
	}
	for(int i = 0; i < this->sizePuz; i++){
		for(int j = 0; j < this->sizePuz; j++){
			number1 = (i*this->sizePuz)+j;
			this->freshGrid[i][j] = number1;;
		}
	}
}

std::vector<std::vector<int> > Puzzle::slide_puzzle(){

	this->SwapsForSolveINDEX1D.clear();	
	int flagtwoRedo = 0;
	int flagSlotting1 = 0;
	int flagSlotting2 = 0;
	int flagSlotting3 = 0;
	int indexNumtoSwap;
	int indexofTwo;
	int indexofSev;
	int indexofThr;
	int indexofFour;	
	int targetIndex = 0;
	std::vector<int>  correctspotsVector;
	correctspotsVector.resize(9);

	for(int i = 0; i < 9; i++){
		if(i == 4 || i == 5){
			i = 6;
		}
		if(i == 3){
			flagSlotting1 = 1;
		}
		else{
			flagSlotting1 = 0;
		}
		if(i == 7){
			flagSlotting2 = 1;
			flagSlotting3 = 1;
		}
		else{
			flagSlotting2 = 0;
		}	
		//This block changes the targets from the index they are to the index they need to be in for the algorithms to work
		targetIndex = i;
		if(targetIndex == 1){	//if target is index 1 it is now 2 for the algorithm
			targetIndex = i + 1;
		}
		else if(targetIndex == 2){
			targetIndex = targetIndex + 3;
		}
		else if(targetIndex == 3){
			targetIndex = targetIndex + 3;
		}
		else if(targetIndex == 6){
			targetIndex = targetIndex + 1;	
		}
		for(int inc100 = 0; inc100 < 3; inc100++){
			for(int inc200 = 0; inc200 < 3; inc200++){
				if(this->startGridPuz[inc100][inc200] == ((inc100*3)+inc200)+1){
					correctspotsVector[((inc100*3)+inc200)] = (((inc100*3)+inc200)+1);
					if((inc200 == 2) && (correctspotsVector[1] == -1) && (inc100 == 0)){
						correctspotsVector[2] = -1;
					}
					if((inc100 == 2) && (inc200 == 0) && (correctspotsVector[3] == -1)){
						correctspotsVector[6] = -1;
					}
				}
				else{
					correctspotsVector[((inc100*3)+inc200)] = -1;
					if((inc200 == 2) && (inc100 == 0)){
						correctspotsVector[1] = -1;
					}
					if((inc100 == 2) && (inc200 == 0)){
						correctspotsVector[3] = -1;
					}
				}
			}
		}
		if(correctspotsVector[i - 1] == -1){
			if(flagSlotting1 == 1){
				flagSlotting1 = 0;
				this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
				this->indexAti	= iIndex0(this->index1D);
				this->indexAtj = jIndex0(this->index1D);
				if(indexAti == 2){
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
					for(int inc40 = 0; inc40 < this->indexAti; inc40++){
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
				else if(this->indexAti == 1){
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
			if(flagSlotting2 == 1){
				flagSlotting2 = 0;
				this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
				this->indexAti	= iIndex0(this->index1D);
				this->indexAtj = jIndex0(this->index1D);
				if(indexAti == 2){
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
				flagSlotting3 = 1;
			}
		}
		if((correctspotsVector[i] == -1) || (i == 7)){	//if the item is not placed correctly in the correct spot vector
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			if((i == 2) && (i >= this->indexAtj)){
				for(int inc5 = 0; inc5 < (1 - this->indexAti); inc5++){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				for(int inc6 = 0; inc6 < ((targetIndex-3) - this->indexAtj); inc6++){
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
				}
				indexofThr = this->findIndex0(3);
				if(indexofThr == 1){		
					this->startGridPuz = this->swapLeft();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
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
					this->startGridPuz = this->swapDown();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
					this->startGridPuz = this->swapLeft();			
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
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
					flagtwoRedo = 1;
				}
			}
			//This if block represents if we are looking for a 1 to swap up
			else if((i <= this->indexAtj) && (i == 0)){
				for(int inc3 = 0; inc3 < (this->indexAtj - i); inc3++){
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0; //remember to do this flag = 0 for mixUP
					}
				}
				for(int inc4 = 0; inc4 < this->indexAti; inc4++){
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
				}
			}
			else if((i == 1) && (i >= this->indexAtj)){
				for(int inc9 = 0; inc9 < (targetIndex - this->indexAtj); inc9++){
					this->startGridPuz = this->swapRight();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(1);
						this->flag = 0;
					}
				}
				for(int inc11 = 0; inc11 < this->indexAti; inc11++){
					this->startGridPuz = this->swapUp();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(2);
						this->flag = 0;
					}
				}
			}
			else if(i == 3){
				indexofFour = this->findIndex0(4);
				indexofSev = this->findIndex0(7);
				if(indexofSev != 7){
					if(indexofSev != 6 || indexofFour != 7){
						for(int inc12 = 0; inc12 < 2; inc12++){
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
				if(indexofSev == 7){
					for(int inc17 = 0; inc17 < 2; inc17++){
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
				}
				else if((indexofSev == 6) && (indexofFour == 7)){
				
					for(int inc90 = 0; inc90 < 2; inc90++){
						this->startGridPuz = this->swapLeft();
						if(this->flag == 1){
							this->SwapsForSolveINDEX1D.push_back(0);
							this->flag = 0;
						}
					}
				}
				if((indexofSev == 6) && (indexofFour == 7)){
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
				indexofSev = this->findIndex0(7);
				indexofFour = this->findIndex0(4);
				if((indexofSev == 4) && (indexofFour == 3)){
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
			}
			else if(i == 6){
				if(this->indexAti == 1){
					
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
			}
			else if(i == 7){
				if(this->indexAti == 1){	
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
				if(this->indexAtj == 2){
				
					this->startGridPuz = this->swapLeft();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(0);
						this->flag = 0;
					}
				}
			}
			indexofTwo = this->findIndex0(2);
			indexofThr = this->findIndex0(3);
			if(i == 1){
				if((indexofTwo == 1) && (indexofThr == 5)){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					continue;
				}
			}
			indexNumtoSwap = this->findIndex0(i + 1);
			this->indexNumi = this->iIndex0(indexNumtoSwap);
			this->indexNumj = this->jIndex0(indexNumtoSwap);
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			this->startGridPuz = this->swapFrom0toNum(this->index1D, indexNumtoSwap);
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d	
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			indexNumtoSwap = this->findIndex0(i + 1);
			this->indexNumi = this->iIndex0(indexNumtoSwap);
			this->indexNumj = this->jIndex0(indexNumtoSwap);
			if(flagSlotting3 == 1){
				if(this->indexAtj == 1){
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
				else if(this->indexAtj == 2){
					if(this->indexAti == 1){
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
				return this->startGridPuz;
			}
			if(flag == 7){
				return this->startGridPuz;
			}
			if(i == 0){
				this->startGridPuz = this->wrapAround(0, targetIndex, this->index1D, indexNumtoSwap);
			
			}
			else if(i == 1){
				this->startGridPuz = this->wrapAround(1, targetIndex, this->index1D, indexNumtoSwap);
			}
			else if(i == 2){
				this->startGridPuz = this->wrapAround(2, targetIndex, this->index1D, indexNumtoSwap);
				flagSlotting1 = 1;
			}
			else if(i == 3){
				this->startGridPuz = this->wrapAround(3, targetIndex, this->index1D, indexNumtoSwap);
				i = i +2;
			}
			else if(i == 6){
				this->startGridPuz = this->wrapAround(6, targetIndex, this->index1D, indexNumtoSwap);
			}
		}
	}
	return this->startGridPuz;
}

std::vector<std::vector<int> > Puzzle::mixUp(){
	
	this->SwapsForMixUpINDEX1D.clear();	
	int secretNum;
	this->randVals.clear();
	srand(time(NULL));
	for(int ii = 0; ii < 100; ii++){
		secretNum = 0 + rand() % ((3+1)-0);
		this->randVals.push_back(secretNum);
	}
	int j = 0;
	for(int i = 0; i < this->randVals.size(); i++){
		if((i%4) == 0){
			for(j = 0; j < this->randVals[i]; j++){
				
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

int Puzzle::jIndex0(int index0){
	int indexOfjAt0 = index0 % this->sizePuz;
	return indexOfjAt0;
}

int Puzzle::iIndex0(int index0){
	
	int indexOfjAt0 = index0 % this->sizePuz;
	int indexOfiAt0 = ((index0 - indexOfjAt0) / this->sizePuz);
	return indexOfiAt0;
}

std::vector<std::vector<int> > Puzzle::swapRight(){
	
	std::vector<std::vector<int> > resulter;
	index1D = findIndex0(0);
	indexAti = iIndex0(index1D);
	indexAtj = jIndex0(index1D);
	resulter = this->startGridPuz;
	if(indexAtj == (sizePuz-1)){
		return resulter;
	}
	resulter[indexAti][indexAtj] = resulter[indexAti][indexAtj+1];
	resulter[indexAti][indexAtj+1] = 0;
	this->numMoves++;
	this->flag = 1;

	return resulter;
}

std::vector<std::vector<int> > Puzzle::swapLeft(){

	std::vector<std::vector<int> > resulter;
	index1D = findIndex0(0);
	indexAti = iIndex0(index1D);
	indexAtj = jIndex0(index1D);
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

std::vector<std::vector<int> > Puzzle::swapUp(){
	
	std::vector<std::vector<int> > resulter;
	index1D = findIndex0(0);
	indexAti = iIndex0(index1D);
	indexAtj = jIndex0(index1D);
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

std::vector<std::vector<int> > Puzzle::swapDown(){

	std::vector<std::vector<int> > resulter;
	index1D = findIndex0(0);
	indexAti = iIndex0(index1D);
	indexAtj = jIndex0(index1D);
	resulter = this->startGridPuz;
	if(indexAti == (this->sizePuz) - 1){
		return resulter;
	}
	resulter[indexAti][indexAtj] = resulter[indexAti+1][indexAtj];
	resulter[indexAti+1][indexAtj] = 0;
	this->numMoves++;
	this->flag = 1;
	
	return resulter;
}

std::vector<std::vector<int> > Puzzle::swapFrom0toNum(int Index1D0, int Index1Dnum){
	
	this->indexAti = this->iIndex0(Index1D0);
	this->indexAtj = this->jIndex0(Index1D0);
	this->indexNumi = this->iIndex0(Index1Dnum);
	this->indexNumj = this->jIndex0(Index1Dnum);
	int flagforSev = 0;
	if(this->startGridPuz[this->indexNumi][this->indexNumj] == 7){
		flagforSev = 1;
	}
	int inc20 = this->indexAtj;
	int incSwap;
	if(inc20 < this->indexNumj ){
		for(inc20 = this->indexAtj; inc20 < indexNumj; inc20++){
			this->startGridPuz = this->swapRight();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(1);
				this->flag = 0;
			}
		}
	}
	if(this->indexAti != 2){
		for(int inc21 = this->indexAti; inc21 < this->indexNumi; inc21++){
			this->startGridPuz = swapDown();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(3);
				this->flag = 0;
			}
		}
	}
	else{
		for(int inc22 = this->indexAti; inc22 > this->indexNumi; inc22--){
			this->startGridPuz = swapUp();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(2);
				this->flag = 0;
			}
		}
	}
	incSwap = this->indexAtj;
	if(incSwap >= this->indexNumj){
		for(incSwap = this->indexAtj; incSwap > this->indexNumj; incSwap--){
			this->startGridPuz = this->swapLeft();
			if(this->flag == 1){
				this->SwapsForSolveINDEX1D.push_back(0);
				this->flag = 0;
			}
		}
	}
	return this->startGridPuz;
}

std::vector<std::vector<int> > Puzzle::wrapAround(int increment, int targetIndex, int Index1D0,
                                          int Index1Dnum){
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
	while(this->startGridPuz[targetIndexi][targetIndexj] != targetNum){
		count++;
		if(this->startGridPuz[targetIndexi][targetIndexj] == targetNum){
			break;
		}
		if(count == 5){
			return this->startGridPuz;
		}
		if((ir == 0) && (this->indexAtj != this->indexNumj-1) && (this->indexAtj != this->indexNumj+1)){
			if(this->indexNumi == 0){
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
				if(this->indexNumj == 2){
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
			else if((this->indexNumi == 1)  && (this->indexNumj !=2)){
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
			}
			else if((this->indexNumi == 1) && (this->indexNumj ==2)){
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
		}
		else if((ir == 0) && (this->indexAtj == this->indexNumj+1)){
			 
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
		else if((ir == 1) && (this->indexAtj != this->indexNumj - 1) && (this->indexAtj != this->indexNumj + 1)){
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
		else if((ir == 1) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti == 1)){
			if(this->indexNumj == 1){
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
		else if((ir == 1) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti == 2)){
			if(this->indexNumj == 1){
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
		else if((ir == 2) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti == 2)){
			if(this->indexNumj == 1){
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
		else if((ir == 2) && (this->indexAtj == this->indexNumj - 1) && (this->indexAti == 1)){
			
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
		else if(ir == 3){
			if(this->indexAti == 1){	
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
				if(this->indexAtj == 2){
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
		else if(ir == 6){
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
	return this->startGridPuz;
}
//}
