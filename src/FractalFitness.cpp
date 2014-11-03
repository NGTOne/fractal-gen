#include "FractalFitness.hpp"
#include "FractalGen.hpp"
#include <libHierGA/HierGA.hpp>
#include <string>
#include <chrono>

FractalFitness::FractalFitness() {

}

PropertiesList * FractalFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	Individual * tempIndividual;
	Genome * tempGenome;
	PropertiesList * returnProperties = new PropertiesList(0);
	Genome ** tempGenomeList = NULL;
	int numGenomes = 0;
	int length = 0;
	int * fullIndexes = NULL;
	GenePool ** fullPools = NULL;

	//Collect the genes for all the fractals
	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		tempGenome = tempIndividual->getGenome();

		int tempLength = tempGenome->getGenomeLength();
		GenePool ** tempPools = tempGenome->getGenePools();
		int * tempIndexes = tempGenome->getGenome();

		tempGenomeList = (Genome**)realloc(tempGenomeList, (sizeof(Genome) * numGenomes) + sizeof(Genome));

		tempGenomeList[numGenomes++] = tempIndividual->getGenome();
	}

	//Get the length of the fully assembled genome and flatten out the
	//tree
	//This will give us the parameters for each transform
	for (int i = 0; i < numGenomes; i++) {
		length += tempGenomeList[i]->getGenomeLength();
		fullIndexes = (int*)realloc(fullIndexes, sizeof(int)*length);
		fullPools = (GenePool**)realloc(fullPools, sizeof(GenePool*)*length);

		int currentInternalIndex = 0;
		int * tempIndexes = tempGenomeList[i]->getGenome();
		GenePool ** tempPools = tempGenomeList[i]->getGenePools();

		for (int k = length - tempGenomeList[i]->getGenomeLength(); k < length; k++) {
			fullIndexes[k] = tempIndexes[currentInternalIndex];
			fullPools[k] = tempPools[currentInternalIndex++];
		}
	}

	free(tempGenomeList);



	return returnProperties;
}
