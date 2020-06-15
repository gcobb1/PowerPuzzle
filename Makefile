PowerPuzzle.wt: SlidePuzzle2.o WtEnvironment.o PowerMain.o
	g++ SlidePuzzle2.o WtEnvironment.o PowerMain.o -o PowerPuzzle.wt -lwthttp -lwt

SlidePuzzle2.o: SlidePuzzle2.cpp
	g++ -std=c++14 -c SlidePuzzle2.cpp -lwthttp -lwt

WtEnvironment.o: WtEnvironment.cpp
	g++ -std=c++14 -c WtEnvironment.cpp -lwthttp -lwt

PowerMain.o: PowerMain.cpp
	g++ -std=c++14 -c PowerMain.cpp -lwthttp -lwt

clean:
	rm *.o PowerPuzzle.wt
