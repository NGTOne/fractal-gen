#include <libHierGA/hierGA.hpp>
#include <string>
#pragma once

class FractalFitness : public FitnessFunction {
	private:

	protected:
	int numTransforms;

	public:
	FractalFitness();
	FractalFitness(int newNumTransforms);
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);
};

class FractalToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};

class TransformToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
