#include <string>

class Transform{
	private:

	protected:
	string variation;
	int xValues[3];
	int yValues[3];

	public:
	Transform(string newVariation, int * newXValues, int * newYalues);

	std::string getVariation();

	std::string toString();
	std::string toString(double weight, double colour);
}
