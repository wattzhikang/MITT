src = src
bin = bin
gen = bin/generated_files

mitt : $(gen)/main.o $(gen)/Planet.o $(gen)/FileReader.o
	g++ $(gen)/main.o $(gen)/Planet.o $(gen)/FileReader.o -g -o $(bin)/mitt

$(gen)/main.o : $(src)/main.cpp $(src)/Planet.hpp
	g++ $(src)/main.cpp -c -g -o $(gen)/main.o

$(gen)/Planet.o : $(src)/Planet.cpp $(src)/Planet.hpp
	g++ $(src)/Planet.cpp -c -g -o $(gen)/Planet.o

$(gen)/FileReader.o : $(src)/FileReader.cpp $(src)/FileReader.hpp
	g++ $(src)/FileReader.cpp -c -g -o $(gen)/FileReader.o
