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

    int getWorkTime() const;
    void setWorkTime(int value);

    int getCooldownTime() const;
    void setCooldownTime(int value);

    string getAbilityName() const;
    void setAbilityName(const string &value);

protected:
    Enums::AbilityStates abilityState;
    string abilityName;
    int manaCost;
    int workTime;
    int currentWorkTime;
    int cooldownTime;
    int currentCooldownTime;
    Scene* parentScenePtr;
};

