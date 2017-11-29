#ifndef ATOMICMODEL
#define ATOMICMODEL

#include "Time.cpp"
#include "Network.cpp"
#include <string>

template <class I, class O>
class AtomicModel{
public:
	virtual void deltaExternal(I input, double e, Time* currentTime) = 0;
	virtual void deltaInternal(Time* currentTime) = 0;
	virtual void deltaConfluent(I input, double e, Time* currentTime) = 0;
	virtual O lambda() = 0;
	virtual double timeAdvance() = 0;
	virtual std::string getType() = 0;
	virtual void setNetwork(Network* n) = 0;
	virtual Time* getLatestTime() = 0;
};

#endif
