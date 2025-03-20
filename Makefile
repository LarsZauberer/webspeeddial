CXX=g++
CXXFLAGS=-O2 -std=c++20 -g -fsanitize=address
src=src
build=build
tests=tests
targets=$(build)/webspeeddial $(build)/tests

all: $(targets) $(tests)

$(build)/webspeeddial: $(build)/webspeeddial.o $(build)/utils.o $(build)/commands.o
	g++ $(CXXFLAGS) -o $(build)/webspeeddial $(build)/webspeeddial.o $(build)/utils.o $(build)/commands.o

$(build)/webspeeddial.o: $(src)/webspeeddial.cpp
	g++ -c $(CXXFLAGS) -o $(build)/webspeeddial.o $(src)/webspeeddial.cpp

$(build)/utils.o: $(src)/utils.cpp
	g++ -c $(CXXFLAGS) -o $(build)/utils.o $(src)/utils.cpp

$(build)/commands.o: $(src)/commands.cpp
	g++ -c $(CXXFLAGS) -o $(build)/commands.o $(src)/commands.cpp

$(build)/tests: $(tests)/tests.cpp $(build)/utils.o
	g++ $(CXXFLAGS) -lCatch2Main -lCatch2 -o $(build)/tests tests/tests.cpp $(build)/utils.o

clean:
	rm -f $(build)/*.o
	rm -f $(targets)
