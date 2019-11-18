.PHONY: clean

SRC = src
BIN = bin
OBJ = obj
TEST = test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors
DynamicLIB = $(SRC)/node.h $(SRC)/file.h $(SRC)/folder.h $(SRC)/link.h $(SRC)/node_iterator.h $(SRC)/null_iterator.h
StaticLIB = $(OBJ)/find_visitor.o $(OBJ)/update_path_visitor.o

all: clean reset $(BIN)/ut_all

$(BIN)/ut_all: $(TEST)/ut_main.cpp $(TEST)/ut_fs.h $(DynamicLIB) $(StaticLIB)
	g++ $(CFLAGS) $(Wfatal) -o $@ $< $(StaticLIB) $(LIB)
	$(BIN)/ut_all

obj/find_visitor.o: $(SRC)/find_visitor.cpp $(SRC)/find_visitor.h $(SRC)/visitor.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

obj/update_path_visitor.o: $(SRC)/update_path_visitor.cpp $(SRC)/update_path_visitor.h $(SRC)/visitor.h
	g++ $(CFLAGS) $(Wfatal) -c $< -o $@

clean:
	rm -f $(BIN)/*
	mkdir -p $(BIN)

reset:
	rm -rf test/test_folder
	cp -r test/test_folder_backup test/test_folder