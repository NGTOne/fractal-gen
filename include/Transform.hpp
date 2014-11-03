#include <string>

class Transform{
	private:

	protected:
	int variationIndex;
	int xValues[3];
	int yValues[3];

	public:
	Transform(newVariationIndex, int * newXValues, int * newYalues);

	std::string toString();
	std::string toString(double weight, double colour);
}
