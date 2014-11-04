#include "FractalFitness.hpp"
#include "Transform.hpp"
#include <libHierGA/HierGA.hpp>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>

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
	for (int i = 0; i < numTransforms; i++) {
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

	unsigned file-time = chrono::system_clock::now().time_since_epoch().count();

	stringstream fileName;
	filename << "fractal-gen-" << file-time;

	//And we write it all to a flame file
	ofstream flameFile;
	flameFile.open(filename.str(), ios::app);

	//First line - we use the system time as the name
	flameFile << "<flames name=\"fractal-gen-" << file-time << "\">\n";

	//This line contains metadata about the particular flame we're
	//looking at - visual and logistical information that doesn't
	//affect the properties of the fractal itself
	flameFile << "<flame name=\"" << file-time << 
                     "\" version=\"Apophysis 7x\" size=\"1920 1080\"" <<
                     "center=\"0 0 0 \" scale=\"300\" oversample=\"1\"" <<
                     "filter=\"0.5\" quality=\"50\" background=\"0 0 0 \"" <<
                     "brightness=\"4\" gamma=\"4\" gamma_threshold=\"0.01\"" <<
                     "estimator_radius=\"9\" estimator_minimum=\"0\"" <<
                     "estimator_curve=\"0.4\" enable_de=\"0\" plugins=\"";

	//We need to write out which variations we used
	for (int i = 0; i < numTransforms-1; i++) {
		flameFile << allTransforms[i]->getVariation() << " ";
	}
	flameFile << allTransforms[numTransforms-1]->getVariation() << "\" ";

	//The rest of the flame descriptor
	//TODO: Find out what the "curves" value does
	flameFile << "new_linear=\"1\"" <<
                     "curves=\"0 0 1 0 0 1 1 1 1 1 1 1 0 0 1 1 1 1 1 1 1 0 0" <<
                     " 1 0 0 1 1 1 1 1 1 1 0 0 1 0 0 1 1 1 1 1 1 1\" >\n";

	//Now we write out our transforms
	for (int i = 0; i < numTransforms; i++) {
		flameFile << allTransforms[i]->toString(1/numTransforms, 0.5*i);
		flameFile << "\n";
	}

	//Write the colour palette
	flameFile << "<palette count=\"256\" format=\"RGB\">\n";
	flameFile << (string)pools[genomeLength-1]->getIndex(indexes[genomeLength-1]);

	//End the file
	flameFile << "</palette>\n</flame>\n</flames>";

	int fitness;

	printf("Please rate flame %s.\n", fileName);
	scanf("%d", &fitness);

	returnProperties = new PropertiesList(fitness);

	return returnProperties;
}
