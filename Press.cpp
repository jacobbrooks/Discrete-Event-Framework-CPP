#ifndef PRESS
#define PRESS

#include "AtomicModel.cpp"
#include "Scheduler.cpp"
#include "Network.cpp"
#include <string>
#include <vector>

using namespace std;

template <class I, class O>
class Press : public AtomicModel<int,int>{

	string type;
	double t;

	int parts;
	double s;

	Scheduler<I,O>* scheduler;
	Network* network;
	vector<Time*> timeLog;

public:

	Press(Scheduler<I,O>* scheduler){
		parts = 0;
		s = 0.0;

		type = "press";
		t = 1.0;

		this -> scheduler = scheduler;

		timeLog.push_back(new Time(0.0, 0));
	}

	void deltaExternal(int q, double e, Time* currentTime){

		if(parts > 0){
			s -= e;
		}else{
			s = t;
		}

		parts += q;

		scheduler -> deleteOutputEvent(currentTime -> getReal(), this);

		Time* newEventTime = new Time(currentTime -> getReal() + timeAdvance(), 0);

		Event<int,int>* pressOutputEvent = new Event<int, int>(network, this, NULL, newEventTime, "output");
		pressOutputEvent -> setE(timeAdvance());

		scheduler -> insert(pressOutputEvent);

		timeLog.push_back(currentTime);
	}

	void deltaInternal(Time* currentTime){

		parts--;
		s = t;

		for(int i = 0; i < network -> size(); i++){
			if(network -> coupleAt(i) -> source == this){
				for(int j = 0; j < network -> coupleAt(i) -> sinks.size(); j++){

					AtomicModel<int,int>* sink = network -> coupleAt(i) -> sinks[j];

					Event<int,int>* drillInputEvent = new Event<int,int>(network, sink, NULL, currentTime, "input");

				}
			}
		}

	}

	double timeAdvance(){
		return 0.0;
	}


};

#endif





























