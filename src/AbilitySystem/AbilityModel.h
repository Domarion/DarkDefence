#pragma once
#include "../Enums.h"
#include <string>
using std::string;
#include "../Grouping/Scene.h"
#include <memory>
#include "../GlobalScripts/ManaGlobal.h"
#include <functional>

class AbilityModel
{
public:
    AbilityModel(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityModel() = default;

    virtual void init(std::shared_ptr<Scene> scenePtr);
    virtual bool onReady(double timestep) = 0;
    virtual bool onWorking(double timestep) = 0;
    virtual bool onCooldown(double timestep);
    virtual bool update(double timestep);
    virtual bool canPlaceObject() const;

    bool trySetAsReady();
    int getManaCost() const;
    void setManaCost(int value);

    double getWorkTime() const;
    void setWorkTime(double value);

    double getCooldownTime() const;
    double getCurrentCooldownTime() const;
    void setCooldownTime(double value);

    string getAbilityName() const;
    void setAbilityName(const string &value);
    void setPlacingCallback(std::function<void()> aPlacingEndedCallBack);

    void connectCooldownListener(std::function<void(int, int)> aMethod);

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

    std::function<void()> placingEndedCallBack;
    std::function<void(int, int)> cooldownListener;
    double currentDelta{0};
    const double spamDelta = 250; // интервал передачи значений
};

