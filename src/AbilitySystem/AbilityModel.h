#pragma once
#include "../Enums.h"
#include <string>
using std::string;
#include "../Grouping/Scene.h"
#include <memory>
#include "../GlobalScripts/ManaGlobal.h"

class AbilityModel
{
public:
    AbilityModel(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityModel();
    virtual void init(std::shared_ptr<Scene> scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep) = 0;
    virtual bool onCooldown(double timestep) = 0;
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
    std::shared_ptr<Scene> parentScenePtr;
    std::shared_ptr<ManaGlobal> mManaModel;
};

