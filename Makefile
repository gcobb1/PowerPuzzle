PowerPuzzle: SlidePuzzle.o WtEnvironment.o PowerMain.o
	g++ SlidePuzzle.o WtEnvironment.o PowerMain.o -o PowerPuzzle -lwthttp -lwt

SlidePuzzle.o: SlidePuzzle.cpp
	g++ -std=c++14 -c SlidePuzzle.cpp -lwthttp -lwt

WtEnvironment.o: WtEnvironment.cpp
	g++ -std=c++14 -c WtEnvironment.cpp -lwthttp -lwt

PowerMain.o: PowerMain.cpp
	g++ -std=c++14 -c PowerMain.cpp -lwthttp -lwt

clean:
	rm *.o PowerPuzzle
