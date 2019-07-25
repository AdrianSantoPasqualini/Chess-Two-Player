#ifndef SUBJ_H
#define SUBJ_H

class State;

class Subject {
	vector<shared_ptr<Observer>> observers;
	State state;
	
	protected:
		void setState(State newState);
	public:
		void notifyObservers();
		void attach(shared_ptr<Observer> o);
		State getState();
};
#endif
