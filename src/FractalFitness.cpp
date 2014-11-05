#include "FractalFitness.hpp"
#include "Transform.hpp"
#include <libHierGA/HierGA.hpp>
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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
	double xCoefs[numTransforms][3];
	double yCoefs[numTransforms][3];

	//Collect the genes for all the fractals
	for (int i = 0; i < numTransforms; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		tempGenome = tempIndividual->getGenome();

		int tempLength = tempGenome->getGenomeLength();
		GenePool ** tempPools = tempGenome->getGenePools();
		int * tempIndexes = tempGenome->getGenome();

		variations[i] = *(string*)tempPools[0]->getIndex(tempIndexes[0]);
		
		for (int k = 1; k < 4; k++) {
			xCoefs[i][k-1] = *(double*)tempPools[k]->getIndex(tempIndexes[k]);
			yCoefs[i][k-1] = *(double*)tempPools[k+3]->getIndex(tempIndexes[k+3]);
		}
	}

	Transform ** allTransforms = (Transform**)malloc(sizeof(Transform*)*numTransforms);

	//Now we create a Transform for each member of our genome
	for (int i = 0; i < numTransforms; i++) {
		allTransforms[i] = new Transform(variations[i], xCoefs[i], yCoefs[i]);
	}

	unsigned fileTime = chrono::system_clock::now().time_since_epoch().count();

	stringstream fileName;
	fileName << "fractal-gen-" << fileTime;

	stringstream fullFileName;
	fullFileName << fileName.str() << ".flame";

	//And we write it all to a flame file
	ofstream flameFile;
	flameFile.open(fullFileName.str(), ios::app);

	//First line - we use the system time as the name
	flameFile << "<flames name=\"fractal-gen-" << fileTime << "\">\n";

	//This line contains metadata about the particular flame we're
	//looking at - visual and logistical information that doesn't
	//affect the properties of the fractal itself
	flameFile << "<flame name=\"" << fileTime << 
                     "\" version=\"Apophysis 7x\" size=\"1920 1080\" " <<
                     "center=\"0 0\" scale=\"300\" oversample=\"1\" " <<
                     "filter=\"0.5\" quality=\"50\" background=\"0 0 0\" " <<
                     "brightness=\"4\" gamma=\"4\" gamma_threshold=\"0.01\" " <<
                     "estimator_radius=\"9\" estimator_minimum=\"0\" " <<
                     "estimator_curve=\"0.4\" enable_de=\"0\" plugins=\"";

	//We need to write out which variations we used, and only do it once
	//for each
	string variationsUsed[numTransforms];
	bool written[numTransforms];

	for (int i = 0; i < numTransforms; i++) {
		variationsUsed[i] = allTransforms[i]->getVariation();
		written[i] = false;
	}

	for (int i = 0; i < numTransforms; i++) {
		string tempVariation = variationsUsed[i];
		for (int k = 0; k < i; k++) {
			if (variationsUsed[k].compare(tempVariation) == 0) {
				written[i] = true;
			}
		}

		if (written[i] == false) {
			flameFile << tempVariation;
			written[i] = true;
		}

		if (i < numTransforms - 1) {
			flameFile << " ";
		}
	}

	flameFile << "\" ";

	//The rest of the flame descriptor
	//TODO: Find out what the "curves" value does
	flameFile << "new_linear=\"1\" " <<
                     "curves=\"0 0 1 0 0 1 1 1 1 1 1 1 0 0 1 0 0 1 1 1 1 1 " <<
                     "1 1 0 0 1 0 0 1 1 1 1 1 1 1 0 0 1 0 0 1 1 1 1 1 1 1\">\n";

	//Now we write out our transforms
	for (int i = 0; i < numTransforms; i++) {
		flameFile << allTransforms[i]->toString(1.0/numTransforms, i*(1.0/numTransforms));
		flameFile << "\n";
	}

	//Write the colour palette
	flameFile << "<palette count=\"256\" format=\"RGB\">\n";
	flameFile << *(string*)pools[genomeLength-1]->getIndex(indexes[genomeLength-1]);

	//End the file
	flameFile << "</palette>\n</flame>\n</flames>";

	flameFile.close();

	int fitness;

	cout << "Please rate flame " << fileName.str() << ".\n";
	scanf("%d", &fitness);

	returnProperties = new PropertiesList(fitness);

	return returnProperties;
}

FractalToString::FractalToString() {
	numTransforms = 0;
}

FractalToString::FractalToString(int newNumTransforms) : numTransforms(newNumTransforms) {}

string FractalToString::toString(GenePool ** pools, int * indexes, int genomeLength) {
	stringstream ss;

	Individual * tempIndividual;

	for (int i = 0; i < numTransforms-1; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		ss << tempIndividual->toString() << "\n";
	}
	
	ss << "Palette index: " << indexes[numTransforms-1] << "\n";

	return ss.str();
}

string TransformToString::toString(GenePool ** pools, int * indexes, int genomeLength) {
	stringstream ss;

	double xcoefs[3];
	double ycoefs[3];
	string variation;

	for (int i = 1; i < 4; i++) {
		xcoefs[i] = *(double*)pools[i]->getIndex(indexes[i]);
		ycoefs[i] = *(double*)pools[i+3]->getIndex(indexes[i+3]);
	}

	variation = *(string*)pools[0]->getIndex(indexes[0]);

	Transform * tempTransform = new Transform(variation, xcoefs, ycoefs);

	ss << tempTransform->toString() << "\n";

	delete(tempTransform);

	return ss.str();
}
