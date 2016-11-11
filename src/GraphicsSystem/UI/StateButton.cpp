#include "StateButton.h"

StateButton::StateButton()
{

}

string StateButton::getState1() const
{
    return state1;
}

void StateButton::setState1(const string &value)
{
    state1 = value;
    setCurrentState(state1);
}

bool StateButton::onClick(Position point)
{
    SDL_Point sPoint{point.x, point.y};

    bool result = SDL_PointInRect(&sPoint, &getRect());

    if (result && connectedMethod != nullptr)
    {
      //  std::cout << "Clicked" << std::endl;

        setCurrentState((currentState == state1)? state2: state1);
        connectedMethod(getCurrentState());
        //TODO: something similar to delegate
    }
    return result;
}

string StateButton::getState2() const
{
    return state2;
}

void StateButton::setState2(const string &value)
{
    state2 = value;
}

string StateButton::getCurrentState() const
{
    return currentState;
}

void StateButton::setCurrentState(const string &value)
{
    currentState = value;
}
