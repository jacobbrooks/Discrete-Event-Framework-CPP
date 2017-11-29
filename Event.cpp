#ifndef EVENT
#define EVENT

#include <string>

#include "AtomicModel.cpp"
#include "Network.cpp"
#include "Time.cpp"

using namespace std;

template <class I, class O>
class Event{
	AtomicModel<I,O>* model;
	Network* network;
	Time* currentTime;
	string eventType;
	double e;
	I input;
	I output;

public:
	Event(Network* network, AtomicModel<I,O>* model, I input, Time* currentTime, string eventType){
		this -> network = network;
		this -> model = model;
		this -> currentTime = currentTime;
		this -> eventType = eventType;
		this -> input = input;
	}

	AtomicModel<I,O>* getModel(){
		return model;
	}

	Time* getTime(){
		return currentTime;
	}

	string getEventType(){
		return eventType;
	}

	void setE(double e){
		this -> e = e;
	}

	I getInput(){
		return input;
	}

	void execute(){

	}

	int compareTo(Event<I,O>* e){
		if(currentTime -> compareTo(e -> getTime()) < 0){
			return -1;
		}else if(currentTime -> compareTo(e -> getTime()) > 0){
			return 1;
		}else{
			if(!model -> getType().compare(e -> getModel() -> getType())){
				if(!e -> getEventType().compare("output")){
					return 1;
				}else if(!eventType.compare("output")){
					return -1;
				}
			}
		}
		return 0;
	}
};

#endif