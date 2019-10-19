.PHONY: clean

SRC = ./src
BIN = ./bin
TEST = ./test
LIB = -lgtest -lpthread
CFLAGS = -std=c++11
Wfatal = -Wfatal-errors

all: clean $(BIN)/ut_all

$(BIN)/ut_all: $(SRC)/ $(test)/
	g++ $(CFLAGS) $(Wfatal) $(TEST)/ut_main.cpp -o $(BIN)/ut_all $(LIB)
	$(BIN)/ut_all

clean:
	rm -f $(BIN)/*
	mkdir -p $(BIN)