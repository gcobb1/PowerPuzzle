





//#include <fstream>
#include "SlidePuzzle.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <Wt/WObject.h>
#include <fstream>
//Puzzle object that is the underlying computational model of the display puzzle

//Puzzle Class Public Method Defs..
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

std::vector<std::vector<int> > Puzzle::slide_puzzle(){
	this->topRowComplete = 0;
	this->sideColComplete = 0;
	this->SwapsForSolveINDEX1D.clear();	
	int flagtwoRedo = 0;
	int someFlag = 0;
	int counterstopInf;
	int randomFlag = 0;
	int flagSlotting1 = 0;
	int flagSlotting2 = 0;
	std::ofstream ofile;
	int flagSlotting3 = 0;
	ofile.open("exampler.txt", std::ios::app);
	int indexNumtoSwap;
	int tempi = 0;
	int tempj = 0;
	int counterSide = 0;
	int counterS = 0;
	int indexofTwo;
	int indexofSev;
	int indexofThr;
	int indexofFour;	
	int targetIndex = 0;
	std::vector<int>  correctspotsVector;
	correctspotsVector.resize((this->sizePuz * this->sizePuz));
	int nonnum = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + 1);
	int nonnum2 = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + (this->sizePuz - 2));
	for(int i = 0; i < (this->sizePuz * this->sizePuz); ++i){
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
		if(someFlag == 1){
			ofile << "Some Flag = 1 and i: " << i << "\n";	
		}
/*	
		
		for(int increment101 = 0; (increment101 < (this->sizePuz - 2)); increment101++){
			if(this->startGridPuz[((this->sizePuz - 2) * this->sizePuz) + increment101] == (nonnum + increment101)){
				if(this->startGridPuz[((this->sizePuz - 1) * this->sizePuz) + increment101] == ((nonnum + increment101) + this->sizePuz)){
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
*/
/*	
		if((i > (nonnum - (1 + this->sizePuz))) && (i < ((this->sizePuz * this->sizePuz) - 1))){
			this->sideColComplete = (i % this->sizePuz);
		}
		ofile << "i: " << std::to_string(i) << "\n";
		ofile << "Side Cols Complete : " << this->sideColComplete << "\n";
		if(this->sideColComplete == this->sizePuz - 2){
			flagSlotting3 = 1;
		}
		else{
			flagSlotting3 = 0;
		}
*/	
		for(int inc100 = 0; inc100 < this->sizePuz; inc100++){
			for(int inc200 = 0; inc200 < this->sizePuz; inc200++){
				if(this->startGridPuz[inc100][inc200] == ((inc100 * this->sizePuz) + inc200) + 1){
					correctspotsVector[((inc100 * this->sizePuz)+inc200)] = (((inc100 * this->sizePuz)+inc200)+1);
					if((inc200 == (this->sizePuz - 1)) && (correctspotsVector[((inc100 * this->sizePuz) + this->sizePuz - 2)] == -1)){// && (inc100 == 0)){
						correctspotsVector[((inc100 * this->sizePuz) + this->sizePuz - 1)] = -1;
					}//stopped here
					if((inc100 == this->sizePuz - 1) && (inc200 < (nonnum2 % this->sizePuz)) && (correctspotsVector[(nonnum - 1) + inc200] == -1)){
						correctspotsVector[((nonnum + (this->sizePuz - 1)) + inc200)] = -1;
					}
				}
				else{
					correctspotsVector[((inc100 * this->sizePuz)+inc200)] = -1;
					if((inc200 == this->sizePuz - 1) && ((inc100 < (1 + this->topRowComplete)))){//1 was topRowComplete
						correctspotsVector[((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))] = -1;//0 was topRowComplete
					}
					if((inc100 == this->sizePuz - 1) && (inc200 < (nonnum2 % this->sizePuz))){
						correctspotsVector[((nonnum - 1) + inc200)] = -1;
					}
				}
			}
		}//lets see
		for(int incrementer001 = 0; incrementer001 < this->sizePuz- 2; incrementer001++){
			if(this->startGridPuz[(this->sizePuz - 1)][incrementer001] != ((((this->sizePuz - 1) * (this->sizePuz)) + incrementer001) + 1)){
				correctspotsVector[(((this->sizePuz - 2) * (this->sizePuz)) + incrementer001)] = -1;
			}
		}
		ofile << "i: " << i << "\n";
		ofile << "CorrectSpotsVector index: ";
		for(int jjjjj = 0; jjjjj < correctspotsVector.size(); jjjjj++){
			ofile << jjjjj << "... Correct? " << correctspotsVector[jjjjj] << "\n";
		}
		ofile << "\n";
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
//			if(correctspotsVector[(((this->sizePuz - 2) * this->sizePuz) + this->sideColComplete)] == -1){
//				i = (((this->sizePuz - 2) * this->sizePuz) + this->sideColComplete);
//			}

		ofile << "Number of sides Complete: " << this->sideColComplete << "\n";
		if((i >= nonnum) && (i < ((this->sizePuz * this->sizePuz) - this->sizePuz))){
			if((this->sideColComplete - (i % this->sizePuz)) != 0){	
				if(correctspotsVector[(((this->sizePuz - 2) * this->sizePuz) + this->sideColComplete)] == -1){
					if(startGridPuz[(this->sizePuz - 2)][this->sideColComplete] == ((((this->sizePuz - 2) * this->sizePuz) + this->sideColComplete) + 1)){
						someFlag = 1;
						randomFlag = 1;
					}
				
				ofile << "I is changed to: ";
				i = (((this->sizePuz * this->sizePuz) - this->sizePuz) + this->sideColComplete);
				ofile << i << "\n";
				ofile << "someFlag: " << someFlag << "\n";
				}
			}//else someFlag = 1???
			//if(someFlag == 1){
			//	someFlag = 0;
			//	i = i - this->sizePuz;
			//}
		}

		if((i > ((nonnum - 1) + this->sizePuz)) && (i < ((nonnum2) + this->sizePuz))){
			if((this->sideColComplete - (i % this->sizePuz)) != 0){
				this->sideColComplete = this->sideColComplete + 1;
				if(i != nonnum2){	//PROBABLY PLUS THIS_> SIZEPUZ 2.1
				//	this->sideColComplete = this->sideColComplete + 1;
					someFlag = 1;
				}
			}
			else{
		//		randomflag = 1;
			}
		}
		else if(i == ((nonnum - 1) + this->sizePuz)){
			//randomFlag = 1;
		}
/*
		if(i > ((nonnum - 1) + this->sizePuz)){
			if((this->sideColComplete - (i % this->sizePuz)) != 0){
				this->sideColComplete = this->sideColComplete + 1;
				if(i != (nonnum2 + (this->sizePuz))){	
				//	this->sideColComplete = this->sideColComplete + 1;
					someFlag = 1;
				}
			}
			else{
		//		randomflag = 1;
			}
		}
*/

//		if((i % this->sizePuz) == 0)){ //Probably going to need to change to SizePuz * number of rows completed
//			if(i != 0)
//			flagSlotting1 = 1;
//		}
		//else{
		//	flagSlotting1 = 0;
		//}//may have a problem where flagis slotting

		if(i == ((nonnum + this->sizePuz) + (this->sideColComplete - 1)) && (this->sideColComplete > 0) && (i <= (nonnum2 + this->sizePuz))){// + sideColComplete
			if((someFlag == 1) &&  (randomFlag == 0)){// ((i % this->sizePuz) == 0)){
				flagSlotting2 = 1;
			}
			else{
				flagSlotting2 = 0;
			}
			if(((i % this->sizePuz) == 1) && (counterS == 0)){
				//counterS++;
				flagSlotting2 = 1;
			}  
		}
		else{
			flagSlotting2 = 0;
		}
		if(i == (((this->sizePuz* this->sizePuz) - 2) - this->sizePuz)){
			i = (this->sizePuz * this->sizePuz) -  3;
		}
		else if(i == (((this->sizePuz* this->sizePuz) - 1) - this->sizePuz)){	
			i = (this->sizePuz * this->sizePuz) -  2;
		}
		else if(i == ((this->sizePuz* this->sizePuz) - 1)){	
			i = (this->sizePuz * this->sizePuz) -  2;
		}
		
		if((i == ((this->sizePuz * this->sizePuz) - 2)) && (randomFlag == 0)){
			flagSlotting2 = 1;	
			flagSlotting3 = 1;
		//	randomFlag = 0;
			
		}
		else{
			flagSlotting3 = 0;
		}	
		//if(i  > ((this->sizePuz * this->sizePuz) - this->sizePuz) && (i != ((this->sizePuz * this->sizePuz) - 2))){
		//	flagSlotting2 = 0;
		//}
		//else if((i > nonnum - 1) && (i < nonnum2)){
	//		flagSlotting2 = 1;
	//	}

		//This block changes the targets from the index they are to the index they need to be in for the algorithms to work
		targetIndex = i;
		if(((targetIndex % this->sizePuz) == (this->sizePuz - 2)) && (i < (nonnum2 - 1))){	//if target is index 1 it is now 2 for the algorithm
			targetIndex = i + 1;
		}
		else if(((targetIndex % this->sizePuz) == (this->sizePuz - 1)) && (i < (nonnum2 - 1))){
			targetIndex = targetIndex + this->sizePuz;
		}
		else if((targetIndex == ((nonnum - 1)  + this->sideColComplete)) && (i < nonnum2)){//INSERT + SIDECOLCOMPLETE TOMRROW
			targetIndex = targetIndex + this->sizePuz;
		}
		else if((targetIndex == (((nonnum + this->sideColComplete) + this->sizePuz) - 1)) && (i < (nonnum2 + this->sizePuz))){
			targetIndex = targetIndex + 1;	
		}
/*
		for(int inc100 = 0; inc100 < this->sizePuz; inc100++){
			for(int inc200 = 0; inc200 < this->sizePuz; inc200++){
				if(this->startGridPuz[inc100][inc200] == ((inc100 * this->sizePuz) + inc200) + 1){
					correctspotsVector[((inc100 * this->sizePuz)+inc200)] = (((inc100 * this->sizePuz)+inc200)+1);
					if((inc200 == (this->sizePuz - 1)) && (correctspotsVector[((inc100 * this->sizePuz) + this->sizePuz - 2)] == -1)){// && (inc100 == 0)){
						correctspotsVector[((inc100 * this->sizePuz) + this->sizePuz - 1)] = -1;
					}//stopped here
					if((inc100 == this->sizePuz - 1) && (inc200 == 0) && (correctspotsVector[nonnum - 1] == -1)){
						correctspotsVector[(nonnum + (this->sizePuz - 1))] = -1;
					}
				}
				else{
					correctspotsVector[((inc100 * this->sizePuz)+inc200)] = -1;
					if((inc200 == this->sizePuz - 1) && ((inc100 < (1 + this->topRowComplete)))){//1 was topRowComplete
						correctspotsVector[((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))] = -1;//0 was topRowComplete
					}
					if((inc100 == this->sizePuz - 1) && (inc200 == 0)){
						correctspotsVector[(nonnum - 1)] = -1;
					}
				}
			}
		}//lets see
		
*/
		if(i == 13){
			ofile<< "someFlag:" << someFlag << "\n";
		}
		if(i != 0){
		if(correctspotsVector[i - 1] == -1){
//			ofile << "made it to the spot\n";
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
			if(flagSlotting2 == 1){
				ofile << "flagSLotting2 Happening and i = " << i << "\n";
				ofile << "Sides Complete: " << this->sideColComplete << "\n";
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
					//ofile << "swapped Left for Flagslotting\n";
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
			//	flagSlotting3 = 1;
			}
		}
		}
		//
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
		
		if((correctspotsVector[i] == -1) || (i == (nonnum2 + this->sizePuz))){	//if the item is not placed correctly in the correct spot vector
			if( i == 36){
				ofile << "What am I doing here?!!!!!!" << "\n";
			}
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			tempi = this->indexAti;
			tempj = this->indexAtj;
			indexofTwo = this->findIndex0((this->sizePuz - 1) + (this->sizePuz * this->topRowComplete));
			indexofThr = this->findIndex0((this->sizePuz + (this->sizePuz * this->topRowComplete)));
			if(((i % this->sizePuz) == (this->sizePuz - 2)) && (i < (nonnum - 1)) && (tempi == (0 + this->topRowComplete))){
				if((indexofTwo == ((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))) && ((indexofThr == ((this->sizePuz - 1) + ((this->topRowComplete + 1) * this->sizePuz))))){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
				}
					continue;
				}
			}////version 1.1// FIXED 1.8
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			tempi = this->indexAti;
			tempj = this->indexAtj;


			
			if(((i % this->sizePuz) == (this->sizePuz - 1)) && (i < nonnum - 1) && ((i% this->sizePuz) >= this->indexAtj)){
				for(int inc5 = 0; inc5 < ((1 + this->topRowComplete) - tempi); inc5++){//0 was topRowComplete
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
				}// FIXED 1.8//probably should add 1 + this
				indexofThr = this->findIndex0((this->sizePuz + (this->sizePuz * this->topRowComplete)));//
				if(indexofThr == ((this->topRowComplete * this->sizePuz) + (this->sizePuz - 2))){		
					ofile << "EDGE CASE FOR 3,2 is CALLED";
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
			else if(((i % this->sizePuz) == 0) && (i < (nonnum - 1))){
					
		//		this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
		//		this->indexAti	= iIndex0(this->index1D);
		//		this->indexAtj = jIndex0(this->index1D);
		//		tempi = this->indexAti;
		//		tempj = this->indexAtj;
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
			}//added temps
			else if(((i % this->sizePuz) < (this->sizePuz - 1)) && (i < (nonnum - 1))&& ((i % this->sizePuz) != 0) && ((i % this->sizePuz) >= tempj)){// && (i >= this->indexAtj)){
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
			}////version 1.1
			else if(((i % this->sizePuz) < (this->sizePuz - 1)) && (i < (nonnum - 1)) && ((i % this->sizePuz) != 0) && ((i % this->sizePuz)< tempj)){// && (i >= this->indexAtj)){
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
			}////version 1.1

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

						//ofile << "Swapping Left for last row i = " << i << " sides  completed = " << this->sideColComplete << "this->sizePuz - 1 - this->sideColComplete = ?\n";
						for(int inc12 = 0; inc12 < (tempj - this->sideColComplete); inc12++){
							ofile << "swappingleft\n";
							this->startGridPuz = this->swapLeft();
							if(this->flag == 1){
								this->SwapsForSolveINDEX1D.push_back(0);
								this->flag = 0;
							}
						}
					}
				}//
				for(int inc13 = 0; inc13 < 1; inc13++){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
				}
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
				}//
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
			}//version 1.2
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
//			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
//			this->indexAti	= iIndex0(this->index1D);
//			this->indexAtj = jIndex0(this->index1D);
			tempi = this->indexAti;
			tempj = this->indexAtj;
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
			}////version 1.1

/*
			indexofTwo = this->findIndex0((this->sizePuz - 1));
			indexofThr = this->findIndex0(this->sizePuz);
			if(((i % this->sizePuz) == (this->sizePuz - 2)) && (i < nonnum - 1)){
				if(((indexofTwo % this->sizePuz) == (this->sizePuz - 2)) && (((indexofThr % this->sizePuz)+ (this->topRowComplete * this->sizePuz)) == ((this->sizePuz - 1) + this->sizePuz))){
					this->startGridPuz = this->swapDown();
					if(this->flag == 1){
						this->SwapsForSolveINDEX1D.push_back(3);
						this->flag = 0;
					}
					continue;
				}
			}////version 1.1
*/
			indexNumtoSwap = this->findIndex0(i + 1);
			this->indexNumi = this->iIndex0(indexNumtoSwap);
			this->indexNumj = this->jIndex0(indexNumtoSwap);
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			this->startGridPuz = this->swapFrom0toNum(this->index1D, indexNumtoSwap);
			//if(correctspotsVector[i] == (i+1)){
			//	continue;
			//}
			this->index1D = findIndex0(0);	//find indexes of 0 in 1d and 2d	
			this->indexAti	= iIndex0(this->index1D);
			this->indexAtj = jIndex0(this->index1D);
			indexNumtoSwap = this->findIndex0(i + 1);
			this->indexNumi = this->iIndex0(indexNumtoSwap);
			this->indexNumj = this->jIndex0(indexNumtoSwap);
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
				//this->checkSolve();
				//if((this->counter < (this->sizePuz * this->sizePuz)) && (counterstopInf < 3)){
				//	i = 0;
				//	counterstopInf++;
				//	continue;
				//}
				//else{
					return this->startGridPuz;
				//}
			}
			if(flag == 7){
				return this->startGridPuz;
			}//
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
			//	i = i + (this->sizePuz - 1);
			}//need to add this if correct is 3
			else if((i >= ((nonnum - 1) + this->sizePuz)) && (i < ((this->sizePuz * this->sizePuz) - 2))){
				this->startGridPuz = this->wrapAround(i, targetIndex, this->index1D, indexNumtoSwap);
			}//
		}
	}
	
	ofile.close();
	return this->startGridPuz;
}

std::vector<std::vector<int> > Puzzle::mixUp(){
	
	this->SwapsForMixUpINDEX1D.clear();	
	int secretNum;
	this->randVals.clear();
	srand(time(NULL));
	for(int ii = 0; ii < ((this->sizePuz * this->sizePuz) * 7) ; ii++){
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
	this->index1D = findIndex0(0);
	this->indexAti = iIndex0(this->index1D);
	this->indexAtj = jIndex0(this->index1D);
	resulter = this->startGridPuz;
	if(indexAtj == (this->sizePuz-1)){
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

std::vector<std::vector<int> > Puzzle::swapFrom0toNum(int Index1D0, int Index1Dnum){
	
	int nonnum = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + 1);
	int nonnum2 = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + (this->sizePuz - 2));
	this->indexAti = this->iIndex0(Index1D0);
	this->indexAtj = this->jIndex0(Index1D0);
	this->indexNumi = this->iIndex0(Index1Dnum);
	this->indexNumj = this->jIndex0(Index1Dnum);
	int flagforSev = 0;
	if(this->startGridPuz[this->indexNumi][this->indexNumj] == ((nonnum - 1) + this->sizePuz)){
		flagforSev = 1;
	}
	int inc20 = this->indexAtj;
	int inc200 = this->indexNumj;
	int incSwap;
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
	if(inc210 != (this->sizePuz - 1)){//
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
///MAYBE??????










std::vector<std::vector<int> > Puzzle::wrapAround(int increment, int targetIndex, int Index1D0,
                                          int Index1Dnum){
//  this will be done after we build a working 10x10
	int nonnum = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + 1);
	int nonnum2 = (((this->sizePuz * this->sizePuz) - (2 * this->sizePuz)) + (this->sizePuz - 2));

	//std::ofstream ofileW;
	
	//ofileW.open("examplerW.txt", std::ios::app);
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
		index1DNUM = this->findIndex0(targetNum);
		INDEX1D0 = this->findIndex0(0);
		this->indexAti = this->iIndex0(INDEX1D0);
		this->indexAtj = this->jIndex0(INDEX1D0);
		this->indexNumi = this->iIndex0(index1DNUM);
		this->indexNumj = this->jIndex0(index1DNUM);

		if(this->startGridPuz[targetIndexi][targetIndexj] == targetNum){
			break;
		}
		if(count == 30){
			return this->startGridPuz;//for error but may not scale to large systems
		}
		if(((ir % this->sizePuz) == 0) && (ir < nonnum - 1) && (this->indexAtj != this->indexNumj-1) && (this->indexAtj != this->indexNumj+1)){
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
			}/*
			else{
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
				}
				else{
					
				}	

			*/	
		}//
		else if(((ir % this->sizePuz) < (this->sizePuz - 2)) && (ir < nonnum - 1) && (this->indexAtj != this->indexNumj + 1) && (this->indexAtj != this->indexNumj - 1) && ((ir % this->sizePuz) != 0)){// && (this->indexAtj < (this->sizePuz - 1))){
			if(this->indexNumi == (0 + this->topRowComplete)){//may have problem here
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
/*
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
*/
			}
		}//stopped
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
			//index1DNUM = this->findIndex0(targetNum);
			//INDEX1D0 = this->findIndex0(0);
			//this->indexAti = this->iIndex0(INDEX1D0);
			//this->indexAtj = this->jIndex0(INDEX1D0);
			//this->indexNumi = this->iIndex0(index1DNUM);
			//this->indexNumj = this->jIndex0(index1DNUM);
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
/*
			index1DNUM = this->findIndex0(targetNum);
			INDEX1D0 = this->findIndex0(0);
			this->indexAti = this->iIndex0(INDEX1D0);
			this->indexAtj = this->jIndex0(INDEX1D0);
			this->indexNumi = this->iIndex0(index1DNUM);
			this->indexNumj = this->jIndex0(index1DNUM);
*/			
		}
		else if(((ir % this->sizePuz) == (this->sizePuz - 1)) && (ir < nonnum - 1) && (this->indexAtj != (this->indexNumj - 1))){// && (this->indexAti == (this->sizePuz - 1))){
			//if(this->indexNumj < (this->sizePuz - 1)){
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
				this->startGridPuz = swapLeft();//if i == sizepuz - 2 and j == 0 this left is redundant and harmful
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
	//ofileW.close();	
	return this->startGridPuz;
}
