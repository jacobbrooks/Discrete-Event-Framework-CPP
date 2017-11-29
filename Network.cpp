#ifndef NETWORK
#define NETWORK

#include <vector>

#include "Couple.cpp"
#include "AtomicModel.cpp"

using namespace std; 

template <class I, class O>
class Network{

	vector<Couple<I,O>*> couples;

public:

	class NetworkBuilder{
		vector<Couple<I,O>*> couples;
	public:

		NetworkBuilder& addCouple(Couple<I,O>* couple){
			couples.push_back(couple);
		}

		Network* build(){
			return new Network(this);
		}

		friend class Network<I,O>;

	};

	Network(NetworkBuilder* networkBuilder){
		this -> couples = networkBuilder -> couples;
	}

	int size() {
		return couples.size();
	}

	bool isSource(AtomicModel<I,O>* model) {
		for(int i = 0; i < couples.size(); i++){
			if(couples[i] -> isSource(model)){
				return true;
			}
		}
		return false;
	}

	bool isSink(AtomicModel<I,O>* model) {
		for(int i = 0; i < couples.size(); i++) {
			if(couples[i] -> isSink(model)) {
				return true;
			}
		}
		return false;
	}

};

#endif