#pragma once

#include <functional>
#include <memory>
#include <string>

#include "../Enums.h"
#include "../Grouping/Scene.h"
#include "../GlobalScripts/ManaGlobal.h"

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
    bool setAsReady();
    int getManaCost() const;
    void setManaCost(int value);

    double getWorkTime() const;
    void setWorkTime(double value);

    double getCooldownTime() const;
    double getCurrentCooldownTime() const;
    void setCooldownTime(double value);

    const std::string& getAbilityName() const;
    void setAbilityName(const std::string& aName);
    void setPlacingCallback(std::function<void()> aPlacingEndedCallBack);
    void connectCooldownListener(std::function<void(int, int)> aMethod);

protected:
    Enums::AbilityStates abilityState;
    std::string abilityName;
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

