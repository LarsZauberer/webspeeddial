CXX=g++
CXXFLAGS=-O2 -march=native -std=c++20 -g -fsanitize=address
LD_FLAGS=-lyaml-cpp
src=src
build=build
tests=tests
targets=$(build)/webspeeddial $(build)/tests

all: $(targets) $(tests)

$(build)/webspeeddial: $(build)/webspeeddial.o $(build)/utils.o $(build)/commands.o $(build)/config.o
	$(CXX) $(CXXFLAGS) $(LD_FLAGS) -o $@ $^

$(build)/tests: $(tests)/tests.cpp $(build)/utils.o $(build)/commands.o $(build)/config.o
	$(CXX) $(CXXFLAGS) $(LD_FLAGS) -lCatch2Main -lCatch2 -o $@ $^

$(build)/%.o: $(src)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(LD_FLAGS) -o $@ $^

clean:
	rm -f $(build)/*.o
	rm -f $(targets)
