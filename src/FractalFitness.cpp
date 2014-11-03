#include "FractalFitness.hpp"
#include "FractalGen.hpp"
#include "Transform.hpp"
#include <libHierGA/HierGA.hpp>
#include <string>
#include <chrono>

FractalFitness::FractalFitness() {
	numTransforms = 0;
}

FractalFitness::FractalFitness(int newNumTransforms): numTransforms(newNumTransforms) {};

PropertiesList * FractalFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	Individual * tempIndividual;
	Genome * tempGenome;
	PropertiesList * returnProperties = new PropertiesList(0);
	Genome ** tempGenomeList = NULL;
	int numGenomes = 0;
	int length = 0;
	int * fullIndexes = NULL;
	GenePool ** fullPools = NULL;
	string variations[numTransforms];
	int xCoefs[numTransforms][3];
	int yCoefs[numTransforms][3];

	//Collect the genes for all the fractals
	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		tempGenome = tempIndividual->getGenome();

		int tempLength = tempGenome->getGenomeLength();
		GenePool ** tempPools = tempGenome->getGenePools();
		int * tempIndexes = tempGenome->getGenome();

		variations[i] = (string)tempPools[0]->getIndex(tempIndexes[0]);
		
		for (int k = 1; k < 4; k++) {
			xCoefs[i][k-1] = *(int*)tempPools[k]->getIndex(tempIndexes[k]);
			yCoefs[i][k-1] = *(int*)tempPools[k+3]->getIndex(tempIndexes[k+3]);
		}
	}

	Transform ** allTransforms = malloc(sizeof(Transform*)*numTransforms);

	//Now we create a Transform for each member of our genome
	for (int i = 0; i < numTransforms; i++) {
		allTransforms[i] = new Transform(variations[i], xCoefs[i], yCoefs[i]);
	}

	return returnProperties;
}
