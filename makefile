.PHONY: clean

SRC = src
BIN = bin
OBJ = obj
TEST = test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors
DynamicLIB = $(SRC)/element.h $(SRC)/integer.h $(SRC)/iterator.h $(SRC)/null_iterator.h $(SRC)/set.h $(SRC)/visitor.h
StaticLIB = $(OBJ)/flattened_set_visitor.o $(OBJ)/evaluate_visitor.o

all: clean mkdir $(BIN)/ut_all

$(BIN)/ut_all: $(TEST)/ut_midterm2.cpp $(DynamicLIB) $(StaticLIB)
	g++ $(CFLAGS) $(Wfatal) -o $@ $< $(StaticLIB) $(LIB)
	$@ --gtest_catch_exceptions=1

obj/flattened_set_visitor.o: $(SRC)/flattened_set_visitor.cpp $(SRC)/flattened_set_visitor.h $(SRC)/visitor.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

obj/evaluate_visitor.o: $(SRC)/evaluate_visitor.cpp $(SRC)/evaluate_visitor.h $(SRC)/visitor.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

mkdir:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)
