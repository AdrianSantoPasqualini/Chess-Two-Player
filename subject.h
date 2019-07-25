#ifndef SUBJ_H
#define SUBJ_H

#include <vector>
#include "state.h"

class Observer;

class Subject {
	vector<shared_ptr<Observer>> observers;
	State state;
	
	protected:
		void setState(State nState) {
			state = nState;
		}
	public:
		void notifyObservers() {
			for (auto &ob : observers) ob->notify(*this);
		}

		void attach(shared_ptr<Observer> o) {
			observers.emplace_back(o);
		}

		State getState() {
			return state;
		}
};
#endif
