#include <string>
#pragma once

class Transform{
	private:

	protected:
	std::string variation;
	int xValues[3];
	int yValues[3];

	public:
	Transform(std::string newVariation, int * newXValues, int * newYalues);

	std::string getVariation();

	std::string toString();
	std::string toString(double weight, double colour);
};
