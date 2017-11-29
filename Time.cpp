#ifndef TIME
#define TIME

class Time{

	double real;
	int discrete;

public:
	Time(double real, int discrete){
		this -> real = real;
		this -> discrete = discrete;
	}

	double getReal(){
		return real;
	}

	int getDiscrete(){
		return discrete;
	}

	int compareTo(Time* t){
		if(this -> real > t -> real){
			return 1;
		}else if(this -> real < t -> real){
			return -1;
		}else if(this -> discrete > t -> discrete){
			return 1;
		}else if(this -> discrete < t -> discrete){
			return -1;
		}
		return 0;
	}

};

#endif

