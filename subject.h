#ifndef SUBJ_H
#define SUBJ_H

#include <vector>
#include "state.h"

class Observer;
struct Info;

class Subject {
	vector<Observer *> observers;
	State state;
		
	public:
		void setState(State nState) {
			state = nState;
		}

		void notifyObservers() {
			for (auto &ob : observers) ob->notify(*this);
		}

		void attach(Observer * o) {
			observers.emplace_back(o);
		}

		State getState() {
			return state;
		}

		virtual Info getInfo() const = 0;
};
#endif
