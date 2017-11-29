#include <iostream>
#include "InputModule.cpp"

#include <limits>

int main(){
	double d = std::numeric_limits<double>::min();
	cout << d << endl;
	return 0;
}