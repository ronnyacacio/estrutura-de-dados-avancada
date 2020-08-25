#include <iostream> 
#include "Array.h"

int main() {
	Array<int> iArray(7);
	Array<double> dArray(12);
 
	for (int i = 0; i < iArray.size(); ++i)
	{
		iArray[i] = i;
		dArray[i] = i + 0.5;
	}
 
	for (int j = iArray.size()-1; j >= 0; --j)
		std::cout << iArray[j] << "\t" << dArray[j] << '\n';
 
	return 0;
}
