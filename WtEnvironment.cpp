/*********

Author: Gavin Cobb
Date: April 2020

The purpose of this file is to hold the implementations of the tableApplication object methods that create the front end mechanism
as well as connect to the backend mechanism designed in SlidePuzzle2.cpp 

********/


//#include <boost/bind.hpp>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTableCell.h>
#include <Wt/WTable.h>
#include <string>
#include <vector>
#include <Wt/WGridLayout.h>
#include <iostream>
#include <Wt/WColor.h>
#include <Wt/WCssDecorationStyle.h>
#include <ctime>
#include <cstdlib>
//#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include "SlidePuzzle.h"
#include "WtEnvironment.h"
#include <Wt/WSlider.h>
#include <Wt/WString.h>
#include <thread>
#include <mutex>
#include <Wt/WImage.h>


//Clears the table attached to the front end and adds the table connected to Power Puzzles backend
void tableApplication::clearAddTable(std::vector<std::vector<int> > startGridPuz2, int index0Tablei, int index0Tablej){ 
	table->clear();
	for(int i = 0; i < (this->size); i++){
		for(int j = 0; j < (this->size); j++){
			if((j != index0Tablej) || (i != index0Tablei)){	//if the indexes correlate to a 0 in the backend the space is blank in frontend
	        		this->elementnum = startGridPuz2[i][j];
	    			this->table->elementAt((i), (j))->addNew<Wt::WText>(std::to_string(this->elementnum));
	    			this->table->elementAt((i),(j))->setStyleClass("td");
			}
			else{
	    			table->elementAt((i), (j))->addNew<Wt::WText>(" ");	
				table->elementAt((i),(j))->setId("t123");
				table->elementAt((i),(j))->setStyleClass("td");
		
			}
				
		}
        }
}


//Contructs the application and deals with client-server manipulations
tableApplication::tableApplication(const Wt::WEnvironment& env)
				: Wt::WApplication(env){

	using namespace std::this_thread;
	using namespace std::chrono;	
	
	//the following block configures the style of the application and necessary configurations for responsiveness 
	this->enableAjax();
	this->addMetaHeader("viewport", "width=device-width, initial-scale=1.0");	
	Wt::WApplication::useStyleSheet("style3.css");	
	Wt::WApplication::setBodyClass("body") ;
	setTitle("Power Puzzle");


	//Widgets are stores in the primary container w2
	Wt::WContainerWidget *w2 = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        w2->setContentAlignment(Wt::AlignmentFlag::Center);	
	table = w2->addWidget(std::make_unique<Wt::WTable>());
	table->setHeaderCount(0);
	table->setWidth(Wt::WLength("50%"));
	table->setHeight(Wt::WLength("700px"));
	//Create Contents of table
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(j == 0 && i == 0){
	    			table->elementAt((i), (j))->addNew<Wt::WText>(" ");	
	    		 	table->elementAt((i),(j))->setId("t123");	
				table->elementAt((i),(j))->setStyleClass("td");
			}
			else{
				elementnum = (i*size)+ j;
	    			table->elementAt((i), (j))->addNew<Wt::WText>(std::to_string(elementnum));
	    			table->elementAt((i),(j))->setStyleClass("td");
			}
		}
	}
	//Set Table Styles	
	this->styler = "number-item" + std::to_string(this->size);	
	table->setStyleClass(styler);
	table->addStyleClass("table-bordered");


        //Create 4 Buttons to move pieces
	Wt::WPushButton *button = w2->addWidget(std::make_unique<Wt::WPushButton>("Right!"));    
        button->setStyleClass("button1");      
	Wt::WPushButton *button2 = w2->addWidget(std::make_unique<Wt::WPushButton>("Left!"));    
        button2->setStyleClass("button2");      
	Wt::WPushButton *button3 = w2->addWidget(std::make_unique<Wt::WPushButton>("Down!"));    
        button3->setStyleClass("button3");      
	Wt::WPushButton *button4 = w2->addWidget(std::make_unique<Wt::WPushButton>("Up!"));
	button4->setStyleClass("button4");
	Wt::WPushButton *button5 = w2->addWidget(std::make_unique<Wt::WPushButton>("Mixer!"));    
        button5->setStyleClass("button5");      
	Wt::WPushButton *button6 = w2->addWidget(std::make_unique<Wt::WPushButton>("Solver!"));
	button6->setStyleClass("button6");
	Wt::WSlider *slider = w2->addNew<Wt::WSlider>();
	slider->resize(200, 25);
	slider->setNativeControl(true);	
	slider->setRange(0, 500);	
	slider->setValue(33);
	slider->setStyleClass("slider");
	Wt::WSlider *slider2 = w2->addNew<Wt::WSlider>();
	slider2->resize(200, 25);
	slider2->setNativeControl(true);	
	slider2->setRange(3, 10);	
	slider2->setValue(3);
	slider2->setStyleClass("slider2");	
	slider2->enableAjax();
	slider->enableAjax();	

	//The following is an introduction style for when the application starts
	image = w2->addWidget(std::make_unique<Wt::WImage>("https://piskel-imgstore-b.appspot.com/img/e0f74185-9fa1-11ea-b04a-fbf190883c80.gif"));
	image2 = w2->addWidget(std::make_unique<Wt::WImage>("https://piskel-imgstore-b.appspot.com/img/511461a6-9fa2-11ea-9bfc-fbf190883c80.gif"));
	image->setStyleClass("intro");
	image2->setStyleClass("intro2");


	//Create a Puzzle object to work as the backend model for the table to get its changed data from
	Puzzle *puzzle = new Puzzle();
	this->startGrid = puzzle->startGridPuz;

	//Creates more widgets in the container and adds styles
	SolidMovesText_ = w2-> addWidget(std::make_unique<Wt::WText>("Number of\nMoves:"));
	SolidMovesText_->setStyleClass("SolidMoves");
        MovesText_ = w2-> addWidget(std::make_unique<Wt::WText>(std::to_string(puzzle->numMoves)));
 	MovesText_->setStyleClass("Moves");
	
        TitleText = w2-> addWidget(std::make_unique<Wt::WText>("Power\nPuzzle!"));
	TitleText->setWordWrap(true);	
	TitleText->setStyleClass("TitleText");
       
	//This is more logic and style for the introduction widgets
	IntroText = w2-> addWidget(std::make_unique<Wt::WText>("Slide the numbers into the blank square using the buttons to solve the puzzle!"));
	IntroText->setWordWrap(true);	
	IntroText->setStyleClass("IntroText");
	if(this->introFlag == 1){
		IntroText->show();
		image->show();
		image2->show();
	}
	else{	
		IntroText->hide();
		image->hide();
		image2->hide();
	}
	
	//More styles and widgets are added to the container.
        speedSolveText = w2-> addWidget(std::make_unique<Wt::WText>("Speed Of Solver"));
 	speedSolveText->setStyleClass("speedSolveText");
        sizeGridText = w2-> addWidget(std::make_unique<Wt::WText>("Size Of Puzzle"));
 	sizeGridText->setStyleClass("sizeGridText");
	Solved = w2->addWidget(std::make_unique<Wt::WText>("SOLVED!!"));
	Solved->setStyleClass("Solved");
	Solved->hide();


	//counter is used to store the amount of numbers in the solved permutation
	//when it equals the size of the puzzle it is solved
	if(puzzle->counter == (this->size * this->size)){
		Solved->show();
	}
	else{
		Solved->hide();
	}

	//function connected to slider object signal that changes speed of solver
	slider->valueChanged().connect([=] {
		this->speedSolve = slider->value();
	});

	//Function connected to Sizer button signal that changes the size of the table
	auto SwapSizer = [=]{
		this->flagToBeginSizer = 1;	
		//must wait for other functions to end before changing
		if((this->flagToBeginFXN == 0) && (this->flagToBeginSolver == 0)){
			if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			this->size = slider2->value();
			puzzle->sizePuz = this->size;	
			Solved->hide();
			puzzle->Fresh();
			puzzle->NGFresh();
			puzzle->startGridPuz.resize(this->size);
			for(int increment1 = 0; increment1 < this->size; increment1++){
				puzzle->startGridPuz[increment1].resize(this->size);
			}
			puzzle->startGridPuz = puzzle->freshGrid;
			this->styler = "number-item" + std::to_string(this->size);
			table->setStyleClass(this->styler);
			
			this->clearAddTable(puzzle->startGridPuz, (this->size - 1), (this->size - 1));
			this->flagToBeginSizer = 0;
		}
	
	};
	slider2->valueChanged().connect(std::bind(SwapSizer));

	//function that correlates to the solver visualizer signal
	//uses a list of steps to solve the puzzle created from the function that solves the backend 
	//clearsadds table based on this list to visualize a solution in the frontend
	auto SwapSolver = [=]{
		//must wait for mix to finish
		if((this->flagToBeginFXN == 0) && (this->begunFlag == 0)){
			if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			this->begunFlag = 1;
			this->flagToBeginSolver = 1;
			puzzle->fillSolveTemp();
			puzzle->index1D = puzzle->findIndex0(0);
			puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
			puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
			puzzle->solveINDEXi = puzzle->indexAti;
			puzzle->solveINDEXj = puzzle->indexAtj;
			puzzle->startGridPuz = puzzle->slide_puzzle();

			//iterates through list to determine how to manipulate the table to visualize a solution.
			//manipulation is based on 0,1,2,3 values corresponding to movements left, right, up, down
			for(int inc10 = 0; inc10 < puzzle->SwapsForSolveINDEX1D.size(); inc10++){
				if(puzzle->SwapsForSolveINDEX1D[inc10] == 0){
						puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj - 1];	
						puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj - 1] = 0;
						puzzle->solveINDEXj = puzzle->solveINDEXj -1;
						sleep_for(milliseconds(this->speedSolve));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi,puzzle->solveINDEXj);
						this->processEvents();
				}
				else if(puzzle->SwapsForSolveINDEX1D[inc10] == 2){
						puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi - 1][puzzle->solveINDEXj];
						puzzle->solveTemp[puzzle->solveINDEXi - 1][puzzle->solveINDEXj] = 0;
						puzzle->solveINDEXi = puzzle->solveINDEXi - 1;
						sleep_for(milliseconds(this->speedSolve));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi, puzzle->solveINDEXj);
						this->processEvents();	
				}
				else if(puzzle->SwapsForSolveINDEX1D[inc10] == 1){
						puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj+1];
						puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj+1] = 0;
						puzzle->solveINDEXj = puzzle->solveINDEXj + 1;
						sleep_for(milliseconds(this->speedSolve));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi, puzzle->solveINDEXj);
						this->processEvents();
				}
				else if(puzzle->SwapsForSolveINDEX1D[inc10] == 3){
						puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi + 1][puzzle->solveINDEXj];
						puzzle->solveTemp[puzzle->solveINDEXi + 1][puzzle->solveINDEXj] = 0;
						puzzle->solveINDEXi = puzzle->solveINDEXi + 1;
						sleep_for(milliseconds(this->speedSolve));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi, puzzle->solveINDEXj);
						this->processEvents();
				}
			}	
			puzzle->checkSolve();
			if(puzzle->counter == (this->size * this->size)){
				Solved->show();
			}
			else{
				Solved->hide();
			}		
			MovesText_->setText(std::to_string(puzzle->numMoves));
			this->flagToBeginSolver = 0;
			this->begunFlag = 0;
			if(this->flagToBeginSizer == 1){
				SwapSizer();
			}
		}
	};	
	button6->clicked().connect(std::bind(SwapSolver));

	//Function that mixes the table based on random number generation
	//list is used to manipulate positions of numbers based on left, right, up, and down values made from backend algorithm
	auto SwapMixer = [=]{

		//the function occurs if no other function is occuring
		if((this->flagToBeginSolver == 0) && (this->begunFlag == 0)){
			this->begunFlag = 1;
			if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			this->flagToBeginFXN = 1;
			Solved->hide();
			puzzle->Fresh();
			puzzle->startGridPuz = puzzle->freshGrid;	
			puzzle->startGridPuz = puzzle->mixUp();
			puzzle->mixINDEXj = this->size - 1;
			puzzle->mixINDEXi = this->size - 1;
			for(int k = 0; k < puzzle->SwapsForMixUpINDEX1D.size(); k++){
				if(puzzle->SwapsForMixUpINDEX1D[k] == 0){
					if(puzzle->mixINDEXj != 0){
						puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj-1];
						puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj-1] = 0;
						puzzle->locationof0MIX = puzzle->locationof0MIX - 1;
						puzzle->mixINDEXj = puzzle->mixINDEXj -1;
						puzzle->flag = 1;
						if(puzzle->flag == 1){
							this->clearAddTable(puzzle->freshGrid, puzzle->mixINDEXi, puzzle->mixINDEXj);
							this->processEvents();
							puzzle->flag = 0;
						} 			
					}
				}
				else if(puzzle->SwapsForMixUpINDEX1D[k] == 1){
					if(puzzle->mixINDEXi != 0){
						puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi-1][puzzle->mixINDEXj];
						puzzle->freshGrid[puzzle->mixINDEXi-1][puzzle->mixINDEXj] = 0;
						puzzle->locationof0MIX = puzzle->locationof0MIX - this->size;
						puzzle->mixINDEXi = puzzle->mixINDEXi -1;
						puzzle->flag = 1;
						if(puzzle->flag == 1){
							this->clearAddTable(puzzle->freshGrid, puzzle->mixINDEXi, puzzle->mixINDEXj);
							this->processEvents();
							puzzle->flag = 0;
						} 			
					}
				}
				else if(puzzle->SwapsForMixUpINDEX1D[k] == 2){
					if(puzzle->mixINDEXj != this->size - 1){
						puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj+1];
						puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj+1] = 0;
						puzzle->locationof0MIX = puzzle->locationof0MIX + 1;
						puzzle->mixINDEXj = puzzle->mixINDEXj +1;
						puzzle->flag = 1;
						if(puzzle->flag == 1){
							this->clearAddTable(puzzle->freshGrid, puzzle->mixINDEXi, puzzle->mixINDEXj);
							this->processEvents();
							puzzle->flag = 0;
						} 			
					}
				}
				else if(puzzle->SwapsForMixUpINDEX1D[k] == 3){
					if(puzzle->mixINDEXi != (this->size - 1)){
						puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi+1][puzzle->mixINDEXj];
						puzzle->freshGrid[puzzle->mixINDEXi+1][puzzle->mixINDEXj] = 0;
						puzzle->locationof0MIX = puzzle->locationof0MIX + this->size;
						puzzle->mixINDEXi = puzzle->mixINDEXi +1;
						puzzle->flag = 1;
						if(puzzle->flag == 1){
							this->clearAddTable(puzzle->freshGrid, puzzle->mixINDEXi, puzzle->mixINDEXj);
							this->processEvents();
						puzzle->flag = 0;
						} 			
					}
				}
			}
			puzzle->numMoves = 0;
			puzzle->locationof0MIX = 0;
			puzzle->mixINDEXi = 0;
			puzzle->mixINDEXj = 0;
			MovesText_->setText(std::to_string(puzzle->numMoves));
			this->begunFlag = 0;	
			this->flagToBeginFXN = 0;
			if(this->flagToBeginSizer == 1){
				SwapSizer();
			}
		}
		
	};
	button5->clicked().connect(std::bind(SwapMixer));
	
	//functon that swaps the number to the left of the blank to the right 	
	auto SwapRighter = [=]{
		if(this->begunFlag == 0){
			if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			//swap the backend model to the right then clearadd the table
			puzzle->startGridPuz = puzzle->swapRight();
			//set indexes for clear table
			puzzle->index1D = puzzle->findIndex0(0);
			puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
			puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
			if(puzzle->flag == 1){
				this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
				puzzle->checkSolve();
				if(puzzle->counter == (this->size * this->size)){
					Solved->show();
				}
				else{
					Solved->hide();
				}
				puzzle->flag = 0;
			}
			//Move Completed reflect change to MovesText
		}	MovesText_->setText(std::to_string(puzzle->numMoves));
	};
	button2->clicked().connect(std::bind(SwapRighter));

	//same as above function but left
	auto SwapLefter = [=]{
		if(this->begunFlag == 0){
				if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			puzzle->startGridPuz = puzzle->swapLeft();
			puzzle->index1D = puzzle->findIndex0(0);
			puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
			puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
			if(puzzle->flag == 1){
				this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
				puzzle->checkSolve();
				if(puzzle->counter == (this->size * this->size)){
					Solved->show();
				}
				else{
					Solved->hide();
				}
				puzzle->flag = 0;
			}
			//Move Completed reflect change to MovesText
			MovesText_->setText(std::to_string(puzzle->numMoves));
		}
	};
	button->clicked().connect(std::bind(SwapLefter));

	//same as above function except up
	auto SwapUpper = [=]{
		if(this->begunFlag ==0){
			if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			puzzle->startGridPuz = puzzle->swapUp();
			puzzle->index1D = puzzle->findIndex0(0);
			puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
			puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
			if(puzzle->flag == 1){
				this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
				puzzle->checkSolve();
				if(puzzle->counter == (this->size * this->size)){
					Solved->show();
				}
				else{
					Solved->hide();
				}
				puzzle->flag = 0;
			}
			//Move Completed reflect change to MovesText
			MovesText_->setText(std::to_string(puzzle->numMoves));
		}
	};
	button3->clicked().connect(std::bind(SwapUpper));
	
	//same as above function but down
	auto SwapDowner = [=]{
		if(this->begunFlag == 0){
			if(introFlag == 1){
				introFlag = 0;
				IntroText->hide();
				image2->hide();
				image->hide();
			}
			puzzle->startGridPuz = puzzle->swapDown();
			puzzle->index1D = puzzle->findIndex0(0);
			puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
			puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
			if(puzzle->flag == 1){
				this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
				puzzle->checkSolve();
				if(puzzle->counter == (this->size * this->size)){
					Solved->show();
				}
				else{
					Solved->hide();
				}
				puzzle->flag = 0;
			}
			//Move Completed reflect change to MovesText
			MovesText_->setText(std::to_string(puzzle->numMoves));
		}	
	};
	button4->clicked().connect(std::bind(SwapDowner));
}
