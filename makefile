.PHONY: clean

SRC = src
BIN = bin
OBJ = obj
TEST = test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors
DynamicLIB = $(SRC)/node.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/link.h $(SRC)/null_iterator.h
StaticLIB = $(OBJ)/filesystem_builder.o obj/update_path_visitor.o# $(OBJ)/find_visitor.o
WXLIB = $(SRC)/ui_folder_tree.h

all: clean mkdir $(BIN)/ut_all $(BIN)/hw8

$(BIN)/ut_all: $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(DynamicLIB) $(StaticLIB)
	g++ $(CFLAGS) $(Wfatal) -o $@ $< $(StaticLIB) $(LIB)
	$@ --gtest_catch_exceptions=1

obj/filesystem_builder.o: $(SRC)/filesystem_builder.cpp $(SRC)/filesystem_builder.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

obj/update_path_visitor.o: $(SRC)/update_path_visitor.cpp $(SRC)/update_path_visitor.h $(SRC)/visitor.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

$(BIN)/hw8: $(SRC)/ui_folder_tree.cpp $(WXLIB)
	g++ $< `wx-config --cxxflags --libs` $(StaticLIB) -o $@
	bin/hw8 test/test_folder/hw

hw8: clean mkdir $(BIN)/hw8_no_test

$(BIN)/hw8_no_test: $(SRC)/ui_folder_tree.cpp $(WXLIB) $(DynamicLIB) $(StaticLIB)
	g++ $< `wx-config --cxxflags --libs` $(Wfatal) $(StaticLIB) -o $(BIN)/hw8
	rm -rf test/test_folder
	cp -r test/test_folder_backup test/test_folder
	bin/hw8 test/test_folder

clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

mkdir:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)
