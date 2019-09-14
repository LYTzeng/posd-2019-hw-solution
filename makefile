.PHONY: clean

all: bin/ut_shape

bin/ut_shape: test/ut_shape.cpp src/circular_sector.h src/ellipse.h src/triangle.h
	g++ -std=c++11 test/ut_shape.cpp -o bin/ut_shape -lgtest -lpthread

clean:
	rm bin/* test/output.txt
