#include "Observer.h"
#include <list>
using std::list;
class Subject
{
public:
    Subject();
    virtual ~Subject();
    void addObserver(Observer* obj);
    void removeObserver(Observer* obj);
private:
    list<Observer*> observerList;
};
