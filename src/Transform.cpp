#include "Transform.cpp"
#include <string>

namespace std;

Transform::Transform(string newVariation, int * newXValues, int * newYValues) : variation(newVariation) {
	for (int i = 0; i < 3; i++) {
		xValues[i] = newXValues[i];
		yValues[i] = newYValues[i];
	}
}

string Transform::getVariation() {
	return variation;
}

string Transform::toString() {
	stringstream ss;

	ss << variation << "=\"1\" coefs=\"";
	
	for (int i = 0; i < 3; i++) {
		ss << xValues[i] << " " << yValues[i] << " ";
	}

	ss << "\" opacity=\"1\"";

	return ss.str();
}

string Transform::toString(double weight, double colour) {
	stringstream ss;

	ss << "<xform weight=\"" << weight << "\" color=\"" << color << "\" ";

	ss << toString() << ">";

	return ss.str();
}
