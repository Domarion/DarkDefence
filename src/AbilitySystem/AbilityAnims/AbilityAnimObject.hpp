#pragma once

#include "Grouping/SceneObject.h"

class AbilityAnimObject : public SceneObject
{
public:
    explicit AbilityAnimObject(double timeToLiveSec);
    virtual ~AbilityAnimObject() = default;

    // SceneObject interface
    virtual bool update(double timestep) override;
    bool isFinished() const;

private:
    double mTimeToLive = 0.0;
};

extern std::shared_ptr<AbilityAnimObject> Make_AbilityAnimObject(const std::string& aName,
        double aTimeToLiveMs,
        std::shared_ptr<RenderingSystem>& aRenderer,
        size_t aDrawPriority);
