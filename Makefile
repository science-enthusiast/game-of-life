BIN=./bin
SRC=./src
TEST=./test

all: $(BIN)/game_of_life $(BIN)/game_of_life.exe $(BIN)/test_gol

$(BIN)/game_of_life: $(SRC)/run_gol.cpp $(BIN)/game_of_life.o $(BIN)/test_helper.o
	g++ -std=c++17 -O3 $^ -o $@

$(BIN)/game_of_life.o: $(SRC)/game_of_life.cpp
	g++ -std=c++17 -O3 -c $< -o $@

$(BIN)/test_helper.o: $(SRC)/test_helper.cpp
	g++ -std=c++17 -O3 -c $< -o $@

$(BIN)/game_of_life.exe: $(SRC)/run_gol.cpp $(BIN)/game_of_life.obj $(BIN)/test_helper.obj
	x86_64-w64-mingw32-g++ -std=c++17 -O3 $^ -o $@

$(BIN)/game_of_life.obj: $(SRC)/game_of_life.cpp
	x86_64-w64-mingw32-g++ -std=c++17 -O3 -c $< -o $@

$(BIN)/test_helper.obj: $(SRC)/test_helper.cpp
	x86_64-w64-mingw32-g++ -std=c++17 -O3 -c $< -o $@

$(BIN)/test_gol: $(TEST)/gol_test.cpp $(BIN)/game_of_life.o $(BIN)/test_helper.o
	g++ -std=c++17 $^ -lcppunit -o $(BIN)/gol_test

clean:
	$(RM) $(BIN)/game_of_life $(BIN)/game_of_life.exe $(BIN)/game_of_life.o \
	      $(BIN)/test_helper.o $(BIN)/game_of_life.obj $(BIN)/test_helper.obj \
		    $(BIN)/gol_test
 
