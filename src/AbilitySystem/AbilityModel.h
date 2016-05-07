#pragma once
#include "../Enums.h"
#include <string>
using std::string;
#include "../Grouping/Scene.h"

class AbilityModel
{
public:
    AbilityModel();
    virtual ~AbilityModel();
    virtual void init(Scene* const scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
    virtual bool update(double timestep);
    void setAsReady();
    int getManaCost() const;
    void setManaCost(int value);

    double getWorkTime() const;
    void setWorkTime(double value);

    double getCooldownTime() const;
    void setCooldownTime(double value);

    string getAbilityName() const;
    void setAbilityName(const string &value);

protected:
    Enums::AbilityStates abilityState;
    string abilityName;
    int manaCost;
    double workTime;
    double currentWorkTime;
    double cooldownTime;
    double currentCooldownTime;
    Scene* parentScenePtr;
};

