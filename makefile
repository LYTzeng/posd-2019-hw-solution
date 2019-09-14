.PHONY: clean

all: clean ut_shape

ut_shape: test/ut_shape.cpp src/circular_sector.h src/ellipse.h src/triangle.h
	g++ -std=c++11 test/ut_shape.cpp -o bin/ut_shape -lgtest -lpthread

clean:
	rm -rf bin/
	mkdir -p bin

