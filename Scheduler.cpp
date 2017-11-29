#ifndef SCHEDULER
#define SCHEDULER

#include <vector>
#include <limits>

#include "Event.cpp"
#include "AtomicModel.cpp"
#include "Network.cpp"
#include "Time.cpp"

using namespace std;

template <class I, class O>
class Scheduler{

	vector<Event<I,O>*> heap;

	void siftUp(int pos){
		if(heap[pos] -> compareTo(heap[pos / 2]) < 0){
			swap(pos, pos / 2);
		}
		if(pos / 2){
			siftUp(pos / 2);
		}
	}

	void siftDown(int pos){
		if(smallerChild(pos) != -1){
			if(heap[pos] -> compareTo(heap[smallerChild(pos)]) > 0){
				int child = smallerChild(pos);
				swap(pos, child);
				siftDown(child);
			}
		}
	}

	int smallerChild(int pos){
		int smallerChild = -1;
		if(pos * 2 > heap.size() - 1){
			return smallerChild;
		}else if((pos * 2) + 1 > heap.size() - 1){
			return pos * 2;
		}
		Event<I,O>* leftChild = heap[pos * 2];
		Event<I,O>* rightChild = heap[(pos * 2) + 1];
		if(leftChild -> compareTo(rightChild) < 0){
			smallerChild = pos * 2;
		}else{
			smallerChild = (pos * 2) + 1;
		}
		return smallerChild;
	}

	void swap(int a, int b){
		Event<I,O>* temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	int indexOf(Event<I,O>* e){
		int index = 0;
		for(int i = 1; i < heap.size(); i++){
			if(heap[i] == e){
				index = i;
			}
		}
		return index;
	}

public:

	Scheduler(){
		double d = numeric_limits<double>::min();
		heap.push_back(NULL, NULL, NULL, new Time(d, 0), "");
	}

	void insert(Event<I,O>* e){
		heap.push_back(e);
		siftUp(heap.size() - 1);
	}

	Event<I,O>* pullTop(){
		if(heap.size() == 2){
			Event<I,O>* min = heap[1];
			heap.erase(heap.begin() + 1);
			return min;
		}else{
			Event<I,O>* min = heap[1];
			Event<I,O>* rightMost = heap[heap.size() - 1];
			heap.erase(heap.begin() + (heap.size() - 1));
			heap[1] = rightMost;
			siftDown(1);
			return min;
		}
	}

	void deleteOutputEvent(double realTime, AtomicModel<I,O>* model){
		for(int i = 1; i < heap.size(); i++){
			if(heap[i] -> getTime() -> getReal() > realTime
				&& !heap[i] -> getEventType.compare("output")
				&& heap[i] -> getModel() == model){

				Event<I,O>* rightMost = heap[heap.size() - 1];
				heap[i] = rightMost;
				heap.erase(heap.begin() + (heap.size() - 1));
				siftDown(i);

			}
		}
	}

	void mergeToConfluent(AtomicModel<I,O>* model, Network* network){
		if(heap.size() > 2){
			Time* currentTime = heap[1] -> getTime();

			bool foundOutput = false;
			bool foundInput = false;
			int outputIndex = -1;
			int inputIndex = -1;

			for(int i = 1; i < heap.size(); i++){
				if(heap[i] -> getModel() == model){
					if(heap[i] -> getTime() -> getReal() == currentTime -> getReal()){
						if(!heap[i] -> getEventType().compare("output")){
							foundOutput = true;
							outputIndex = i;
						}
						if(!heap[i] -> getEventType().compare("input")){
							foundInput = true;
							inputIndex = i;
						}
					}
				}
			}

			if(foundOutput && foundInput){
				Event<I,O>* tempInputEvent = heap[inputIndex];
				Event<I,O>* outputEvent = heap[outputIndex];

				Event<I,O>* rightMost = heap[heap.size() - 1];
				inputIndex = indexOf(tempInputEvent);
				heap[inputIndex] = rightMost;
				heap.erase(heap.begin() + (heap.size() - 1));
				siftDown(inputIndex);

				rightMost = heap[heap.size() - 1];
				outputIndex = indexOf(outputEvent);
				heap[outputIndex] = rightMost;
				heap.erase(heap.begin() + (heap.size() - 1));
				siftDown(outputIndex);

				Event<I,O>* confluentEvent = new Event<I,O>(network, model, tempInputEvent -> getInput(), currentTime, "confluent");
				confluentEvent -> setE(0.0);

				insert(confluentEvent);
			}
		}
	}

	bool isEmpty(){
		if(heap.size() < 2){
			return true;
		}
		return false;
	}

};

#endif




























