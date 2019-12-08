.PHONY: clean

SRC = src
BIN = bin
OBJ = obj
TEST = test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors
DynamicLIB = $(SRC)/node.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/link.h $(SRC)/null_iterator.h
StaticLIB = $(OBJ)/filesystem_builder.o # $(OBJ)/find_visitor.o $(OBJ)/update_path_visitor.o 

all: clean mkdir $(BIN)/ut_all

$(BIN)/ut_all: $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(DynamicLIB) $(StaticLIB)
	g++ $(CFLAGS) $(Wfatal) -o $@ $< $(StaticLIB) $(LIB)
	$@ --gtest_catch_exceptions=1

obj/filesystem_builder.o: $(SRC)/filesystem_builder.cpp $(SRC)/filesystem_builder.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

mkdir:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

