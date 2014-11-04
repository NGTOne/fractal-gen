#include <string>
#pragma once

class Transform{
	private:

	protected:
	std::string variation;
	double xValues[3];
	double yValues[3];

	public:
	Transform(std::string newVariation, double * newXValues, double * newYalues);

	std::string getVariation();

	std::string toString();
	std::string toString(double weight, double colour);
};
