CXX=g++
CXXFLAGS=-O2 -std=c++20
src=src
build=build
targets=$(build)/webspeeddial

all: $(targets)

$(build)/webspeeddial: $(build)/webspeeddial.o $(build)/utils.o $(build)/commands.o
	g++ $(CXXFLAGS) -o $(build)/webspeeddial $(build)/webspeeddial.o $(build)/utils.o $(build)/commands.o

$(build)/webspeeddial.o: $(src)/webspeeddial.cpp
	g++ -c $(CXXFLAGS) -o $(build)/webspeeddial.o $(src)/webspeeddial.cpp

$(build)/utils.o: $(src)/utils.cpp
	g++ -c $(CXXFLAGS) -o $(build)/utils.o $(src)/utils.cpp

$(build)/commands.o: $(src)/commands.cpp
	g++ -c $(CXXFLAGS) -o $(build)/commands.o $(src)/commands.cpp

clean:
	rm -f $(build)/*.o
	rm -f $(build)/webspeeddial
