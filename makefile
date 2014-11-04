CPPC = g++
CPPFLAGS = -c -g -std=gnu++0x
INCLUDE = -Iinclude

SHAREDLIB = -lHierGA

all:
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/Transform.cpp -o obj/Transform.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/FractalFitness.cpp -o obj/FractalFitness.o
	$(CPPC) $(CPPFLAGS) $(INCLUDE) src/FractalGen.cpp -o obj/FractalGen.o

	$(CPPC) -o fractal-gen obj/*.o $(SHAREDLIB)

clean:
	rm -f fractal-gen
	rm -f obj/*.o
