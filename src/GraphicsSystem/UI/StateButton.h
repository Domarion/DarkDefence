#pragma once
#include "ImageButton.h"

class StateButton : public ImageButton
{
public:
    StateButton();


    string getState1() const;
    void setState1(const string &value);
    virtual bool onClick(Position point) override;
    string getState2() const;
    void setState2(const string &value);

    string getCurrentState() const;



private:
    void setCurrentState(const string &value);
    string state1, state2, currentState;
};

