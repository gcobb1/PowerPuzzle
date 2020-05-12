#ifndef Wt_Environment_H
#define Wt_Environment_H
//#include <boost/bind.hpp>
#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <string>
#include <vector>
#include <Wt/WColor.h>
#include <cstdlib>
#include "SlidePuzzle.h"

class Puzzle;
//Table Application Class inherit WApplication
class tableApplication : public Wt::WApplication
{
public:
	//Constructor Widget Environment called at run
        tableApplication(const Wt::WEnvironment& env);
	void clearAddTable(std::vector<std::vector<int> > startGridPuz2, int index0Tablei, int index0Tablej); 
	int elementnum = 0;	//index of number in 2D Vector in 1D
protected:
	Wt::WText *Solved;
        Wt::WLineEdit *nameEdit_;
	Wt::WText *SolidMovesText_;
	Wt::WText *counterT;
	Wt::WText *MovesText_;
        Wt::WText *greeting_;
        Wt::WTable *table;
	Wt::Signal<int> gridUpdated;
        std::vector<std::vector<int> > startGrid;    //2D Vector from slide puzzle that c
        std::vector<int> vectorofTableRow; 
        Wt::WText *index0;
        int indexofFrom;
	int indexofTo;
	int size = 3;
	int indexOF0 = 3;
	Wt::WColor *Color;
};
#endif
