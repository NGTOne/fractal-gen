#include "FractalFitness.hpp"
#include "FractalGen.hpp"
#include <libHierGA/HierGA.hpp>
#include <string>

namespace std;

int main(void) {
	int numTransforms = 5;

	GenePool *** baseGenes = (GenePool***)malloc(sizeof(GenePool**) * numTransforms);

	for (int i = 0; i < numTransforms; i++) {
		//Each transform has 7 parameters
		//One variation, and the 6 coefficient locations
		//In practice, multiple variations for a single transform
		//are possible, but we'll keep it simple for now
		//TODO: Make it possible for one transform to use multiple
		//variations
		baseGenes[i] = (GenePool**)malloc(sizeof(GenePool*) * 7);
		baseGenes[i][0] = new NonHierarchicalGenePool<string>(VARIATIONS, sizeof(VARATIONS)/sizeof(string));
	}

	//Set up the bottom level of the hierarchy
	//Each Individual at this level deals with parameters for transforms
	//
	SelectionStrategy ** bottomStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*) * numTransforms);
	GenerationModel ** bottomLevelModels = (GenerationModel**)malloc(sizeof(GenerationModel*) * numTransforms);
	CrossoverOperation ** bottomLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*) * numTransforms);
	MutationOperation ** bottomLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*) * numTransforms);

	FitnessPropagator * myPropagator = new DownPropagator();
	ToStringFunction * myToString = new FractalToString();
	
	for (int i = 0; i < numTransforms; i++) {
		bottomLevelStrategies[i] = new TournamentSelection(0.5);
		bottomLevelModels[i] = new GAGeneration(2, bottomLevelStrategies[i][k]);
		bottomLevelCrossovers[i] = new NPointCrossover(2);
		bottomLevelMutations[i] = new UniformMutation(0.2);
	}
}
