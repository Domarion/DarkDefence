#include "Observer.h"
#include <list>
using std::list;

class Subject
{
public:
    Subject();
    ~Subject();
    void addObserver(Observer* obj);
    void removeObserver(Observer* obj);
    void notify();
private:
    list<Observer*> observerList;
};
