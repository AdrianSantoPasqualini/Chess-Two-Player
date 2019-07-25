#ifndef OBS_H
#define OBS_H

using namespace std;

class Observer {
	
	public:
		virtual void notify(Subject & whoFrom) = 0;
		virtual ~Observer() = default;
};
#endif
