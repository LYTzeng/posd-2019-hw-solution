.PHONY: clean

SRC = src
BIN = bin
OBJ = obj
TEST = test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors
DynamicLIB = $(SRC)/element.h $(SRC)/integer.h $(SRC)/iterator.h $(SRC)/null_iterator.h $(SRC)/set.h $(SRC)/visitor.h
StaticLIB = $(OBJ)/find_visitor.o $(OBJ)/update_path_visitor.o

all: clean $(BIN)/ut_all

$(BIN)/ut_all: $(TEST)/ut_midterm2.cpp $(DynamicLIB) # $(StaticLIB)
	g++ $(CFLAGS) $(Wfatal) -o $@ $< $(LIB) #$(StaticLIB) 
	$@ --gtest_catch_exceptions=1

# obj/find_visitor.o: $(SRC)/find_visitor.cpp $(SRC)/find_visitor.h $(SRC)/visitor.h
# 	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

# obj/update_path_visitor.o: $(SRC)/update_path_visitor.cpp $(SRC)/update_path_visitor.h $(SRC)/visitor.h
# 	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

mkdir:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)
