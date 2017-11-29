#ifndef COUPLE
#define COUPLE

#include <vector>

#include "AtomicModel.cpp"

using namespace std;

template <class I, class O>
class Couple{
public:
	AtomicModel<I,O>* source;
	vector<AtomicModel<I,O>*> sinks;
	O input;

	class CoupleBuilder{
		AtomicModel<I,O>* builderSource;
		vector<AtomicModel<I,O>*> builderSinks;
	public:
		CoupleBuilder& addSource(AtomicModel<I,O>* model){
			builderSource = model;
		}

		CoupleBuilder& addSink(AtomicModel<I,O>* model){
			builderSinks.push_back(model);
		}

		Couple* build(){
			return new Couple(this);
		}

		friend class Couple<I,O>;

	};

	Couple(CoupleBuilder* coupleBuilder){
		this -> source = coupleBuilder -> builderSource;
		this -> sinks = coupleBuilder -> builderSinks;
	}

	void storeLambdaToInput(){
		input = source -> lambda();
	}

	bool isSource(AtomicModel<I,O>* model) {
		if(source == model) {
			return true;
		}
		return false;
	}

	bool isSink(AtomicModel<I,O>* model) {
		for(int i = 0; i < sinks.size(); i++) {
			if(sinks[i] == model) {
				return true;
			}
		}
		return false;
	}

};

#endif