#ifndef INPUTMODULE
#define INPUTMODULE

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class InputModule{

	ifstream file; 
	vector<string> inputs;

	void readFile(){
		string line;
		while(getline(file, line)){
			inputs.push_back(line);
		}
	}

public:

	InputModule(string fileName){
		file.open(fileName);
		readFile();
	}

	double timeAt(int i){
		string s = inputs[i];
		string delimiter = ",";
		string realTime = s.substr(0, s.find(delimiter));
		double d = stod(realTime);
		return d;
	}	

	int inputAt(int i){
		string s = inputs[i];
		string delimiter = ",";
		string input = s.substr(s.find(delimiter) + 1, 1);
		int n = input[0] - '0';
		return n;
	}

	int fileSize(){
		return inputs.size();
	}

};

#endif