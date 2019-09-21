.PHONY: clean

all: clean bin/ut_all

bin/ut_all: test/main.cpp test/ut_shape.h src/circular_sector.h src/ellipse.h src/triangle.h
	g++ -std=c++11 test/main.cpp -o bin/ut_all -lgtest -lpthread

clean:
	rm -f bin/*
	mkdir -p bin

