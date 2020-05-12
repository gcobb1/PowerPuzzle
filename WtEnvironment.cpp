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

void tableApplication::clearAddTable(std::vector<std::vector<int> > startGridPuz2, int index0Tablei, int index0Tablej){ 
	table->clear();
	for(int i = 0; i < (this->size); i++){
		for(int j = 0; j < (this->size); j++){
			if(j == index0Tablej && i == index0Tablei){
	    			table->elementAt((i), (j))->addNew<Wt::WText>(" ");	
	    			table->elementAt((i),(j))->setStyleClass("tr");
			}
			else{
	        		this->elementnum = startGridPuz2[i][j];
	    			this->table->elementAt((i), (j))->addNew<Wt::WText>(std::to_string(this->elementnum));
	    			this->table->elementAt((i),(j))->setStyleClass("tr");
			}
		}
        }
}

tableApplication::tableApplication(const Wt::WEnvironment& env)
				: Wt::WApplication(env){
	using namespace std::this_thread;
	using namespace std::chrono;	
	Wt::WApplication::useStyleSheet("style.css");
	Wt::WApplication::setBodyClass("body") ;
	setTitle("Power Puzzle");
	Wt::WContainerWidget *w2 = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        w2->setContentAlignment(Wt::AlignmentFlag::Center);	
	table = w2->addWidget(std::make_unique<Wt::WTable>());
	table->setHeaderCount(0);
	table->setWidth(Wt::WLength("50%"));
	//Create Contents of table
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(j == 0 && i == 0){
	    			table->elementAt((i), (j))->addNew<Wt::WText>(" ");	
	    			table->elementAt((i),(j))->setStyleClass("tr");
			}
			else{
				elementnum = (i*size)+ j;
	    			table->elementAt((i), (j))->addNew<Wt::WText>(std::to_string(elementnum));
	    			table->elementAt((i),(j))->setStyleClass("tr");
			}
		}
	}
	//Set Table Styles	
	table->setStyleClass("number-item");
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
	Wt::WPushButton *button5 = w2->addWidget(std::make_unique<Wt::WPushButton>("MixUp!"));    
        button5->setStyleClass("button5");      
	Wt::WPushButton *button6 = w2->addWidget(std::make_unique<Wt::WPushButton>("Algoithm Visualizer!\n(Solve with AI)"));
	button6->setStyleClass("button6");
	//Create a Puzzle object to work as the model for the table to get its changed data from
	Puzzle *puzzle = new Puzzle();
	this->startGrid = puzzle->startGridPuz;
	SolidMovesText_ = w2-> addWidget(std::make_unique<Wt::WText>("Number of\nMoves:"));
	SolidMovesText_->setStyleClass("SolidMoves");
        MovesText_ = w2-> addWidget(std::make_unique<Wt::WText>(std::to_string(puzzle->numMoves)));
 	MovesText_->setStyleClass("Moves");
	Solved = w2->addWidget(std::make_unique<Wt::WText>("SOLVED!!"));
	Solved->setStyleClass("Solved");
	Solved->hide();
	if(puzzle->counter == 9){
		Solved->show();
	}
	else{
		Solved->hide();
	}
	//function called when button for visualizer is clicked
	auto SwapSolver = [=]{
		puzzle->fillSolveTemp();
		puzzle->index1D = puzzle->findIndex0(0);
		puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
		puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
		puzzle->solveINDEXi = puzzle->indexAti;
		puzzle->solveINDEXj = puzzle->indexAtj;
		puzzle->startGridPuz = puzzle->slide_puzzle();
		for(int inc10 = 0; inc10 < puzzle->SwapsForSolveINDEX1D.size(); inc10++){
			if(puzzle->SwapsForSolveINDEX1D[inc10] == 0){
				if(puzzle->solveINDEXj != 0){
					puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj - 1];	
					puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj - 1] = 0;
					puzzle->solveINDEXj = puzzle->solveINDEXj -1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
						sleep_for(milliseconds(100));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi,puzzle->solveINDEXj);
						this->processEvents();
						puzzle->flag = 0;
					}
				}
			}
			else if(puzzle->SwapsForSolveINDEX1D[inc10] == 2){
				if(puzzle->solveINDEXi != 0){
					puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi - 1][puzzle->solveINDEXj];
					puzzle->solveTemp[puzzle->solveINDEXi - 1][puzzle->solveINDEXj] = 0;
					puzzle->solveINDEXi = puzzle->solveINDEXi - 1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
						sleep_for(milliseconds(100));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi, puzzle->solveINDEXj);
						this->processEvents();	
						puzzle->flag = 0;
					}
				}
			}
			else if(puzzle->SwapsForSolveINDEX1D[inc10] == 1){
				if(puzzle->solveINDEXj != 2){
					puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj+1];
					puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj+1] = 0;
					puzzle->solveINDEXj = puzzle->solveINDEXj + 1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
						sleep_for(milliseconds(100));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi, puzzle->solveINDEXj);
						this->processEvents();
						puzzle->flag = 0;
					}
				}
			}
			else if(puzzle->SwapsForSolveINDEX1D[inc10] == 3){
				if(puzzle->solveINDEXi != 2){
					puzzle->solveTemp[puzzle->solveINDEXi][puzzle->solveINDEXj] = puzzle->solveTemp[puzzle->solveINDEXi + 1][puzzle->solveINDEXj];
					puzzle->solveTemp[puzzle->solveINDEXi + 1][puzzle->solveINDEXj] = 0;
					puzzle->solveINDEXi = puzzle->solveINDEXi + 1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
						sleep_for(milliseconds(100));
						this->clearAddTable(puzzle->solveTemp, puzzle->solveINDEXi, puzzle->solveINDEXj);
						this->processEvents();
						puzzle->flag = 0;
					}
				}
			}
		}	
		puzzle->checkSolve();
		if(puzzle->counter == 9){
			Solved->show();
		}
		else{
			Solved->hide();
		}		
		MovesText_->setText(std::to_string(puzzle->numMoves));
	};
	button6->clicked().connect(std::bind(SwapSolver));
	
	auto SwapMixer = [=]{
		Solved->hide();
		puzzle->Fresh();
		puzzle->startGridPuz = puzzle->freshGrid;	
		puzzle->startGridPuz = puzzle->mixUp();
		for(int k = 0; k < puzzle->SwapsForMixUpINDEX1D.size(); k++){
			if(puzzle->SwapsForMixUpINDEX1D[k] == 0){
				if(puzzle->mixINDEXj != 0){
					puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj-1];
					puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj-1] = 0;
					puzzle->locationof0MIX = puzzle->locationof0MIX - 1;
					puzzle->mixINDEXj = puzzle->mixINDEXj -1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
						    sleep_for(milliseconds(25));
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
					puzzle->locationof0MIX = puzzle->locationof0MIX - 3;
					puzzle->mixINDEXi = puzzle->mixINDEXi -1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
					        sleep_for(milliseconds(25));
						this->clearAddTable(puzzle->freshGrid, puzzle->mixINDEXi, puzzle->mixINDEXj);
						this->processEvents();
						puzzle->flag = 0;
					} 			
				}
			}
			else if(puzzle->SwapsForMixUpINDEX1D[k] == 2){
				if(puzzle->mixINDEXj != 2){
					puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj+1];
					puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj+1] = 0;
					puzzle->locationof0MIX = puzzle->locationof0MIX + 1;
					puzzle->mixINDEXj = puzzle->mixINDEXj +1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
    						sleep_for(milliseconds(25));
						this->clearAddTable(puzzle->freshGrid, puzzle->mixINDEXi, puzzle->mixINDEXj);
						this->processEvents();
						puzzle->flag = 0;
					} 			
				}
			}
			else if(puzzle->SwapsForMixUpINDEX1D[k] == 3){
				if(puzzle->mixINDEXi != 2){
					puzzle->freshGrid[puzzle->mixINDEXi][puzzle->mixINDEXj] = puzzle->freshGrid[puzzle->mixINDEXi+1][puzzle->mixINDEXj];
					puzzle->freshGrid[puzzle->mixINDEXi+1][puzzle->mixINDEXj] = 0;
					puzzle->locationof0MIX = puzzle->locationof0MIX + 3;
					puzzle->mixINDEXi = puzzle->mixINDEXi +1;
					puzzle->flag = 1;
					if(puzzle->flag == 1){
    						sleep_for(milliseconds(25));
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
	};
	button5->clicked().connect(std::bind(SwapMixer));

	auto SwapRighter = [=]{
		puzzle->startGridPuz = puzzle->swapRight();
		//set indexes for clear table
		puzzle->index1D = puzzle->findIndex0(0);
		puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
		puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
		if(puzzle->flag == 1){
			this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
			puzzle->checkSolve();
			if(puzzle->counter == 9){
				Solved->show();
			}
			else{
				Solved->hide();
			}
			puzzle->flag = 0;
		}
		//Move Completed reflect change to MovesText
		MovesText_->setText(std::to_string(puzzle->numMoves));
	};
	button2->clicked().connect(std::bind(SwapRighter));

	auto SwapLefter = [=]{
		puzzle->startGridPuz = puzzle->swapLeft();
		puzzle->index1D = puzzle->findIndex0(0);
		puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
		puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
		if(puzzle->flag == 1){
			this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
			puzzle->checkSolve();
			if(puzzle->counter == 9){
				Solved->show();
			}
			else{
				Solved->hide();
			}
			puzzle->flag = 0;
		}
		//Move Completed reflect change to MovesText
		MovesText_->setText(std::to_string(puzzle->numMoves));
	};
	button->clicked().connect(std::bind(SwapLefter));

	auto SwapUpper = [=]{
		puzzle->startGridPuz = puzzle->swapUp();
		puzzle->index1D = puzzle->findIndex0(0);
		puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
		puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
		if(puzzle->flag == 1){
			this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
			puzzle->checkSolve();
			if(puzzle->counter == 9){
				Solved->show();
			}
			else{
				Solved->hide();
			}
			puzzle->flag = 0;
		}
		//Move Completed reflect change to MovesText
		MovesText_->setText(std::to_string(puzzle->numMoves));
	};
	button3->clicked().connect(std::bind(SwapUpper));

	auto SwapDowner = [=]{
		puzzle->startGridPuz = puzzle->swapDown();
		puzzle->index1D = puzzle->findIndex0(0);
		puzzle->indexAti = puzzle->iIndex0(puzzle->index1D);
		puzzle->indexAtj = puzzle->jIndex0(puzzle->index1D);
		if(puzzle->flag == 1){
			this->clearAddTable(puzzle->startGridPuz, puzzle->indexAti, puzzle->indexAtj);
			puzzle->checkSolve();
			if(puzzle->counter == 9){
				Solved->show();
			}
			else{
				Solved->hide();
			}
			puzzle->flag = 0;
		}
		//Move Completed reflect change to MovesText
		MovesText_->setText(std::to_string(puzzle->numMoves));
	};
	button4->clicked().connect(std::bind(SwapDowner));
}
