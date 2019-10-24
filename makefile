.PHONY: clean

SRC = ./src
OBJ = ./obj
BIN = ./bin
TEST = ./test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors

all: clean $(BIN)/ut_all

$(BIN)/ut_all: $(TEST)/ut_main.cpp $(SRC)/circular_sector.h $(SRC)/ellipse.h $(SRC)/triangle.h  $(SRC)/sort.h $(SRC)/shape.h $(SRC)/main.cpp $(TEST)/ut_sort.h $(SRC)/terminal.h
	g++ $(CFLAGS) $(Wfatal) $(TEST)/ut_main.cpp -o $(BIN)/ut_all $(LIB)

clean:
	rm -f $(BIN)/*
	mkdir -p $(BIN)

hw3: $(BIN)/geo

$(BIN)/geo: $(SRC)/main.cpp
	g++ $(CFLAGS) $(Wfatal) $(SRC)/main.cpp -o $(BIN)/geo $(LIB)