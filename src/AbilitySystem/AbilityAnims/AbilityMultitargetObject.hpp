#pragma once

#include <functional>

#include "Grouping/SceneObject.h"

class AbilityMultitargetObject : public SceneObject
{
    enum class StateT: int {CollectTargets = 0, ProcessTargets, Move, EndWork};
    using SceneObjectList = std::list<std::shared_ptr<SceneObject>>;
public:
    using CallBackT = std::function<void(std::shared_ptr<SceneObject>)>;
    AbilityMultitargetObject() = default;
    explicit AbilityMultitargetObject(size_t aTargetCount);
    virtual ~AbilityMultitargetObject() = default;
    virtual bool update(double aTimeStep) override;
    void SetCallBack(CallBackT aHandler);
private:
    void CollectTargets();
    void ProcessTargets();
    void EndWork();
    void MoveToTarget();
    size_t mTargetCount = 0;
    StateT mState = StateT::CollectTargets;
    std::unique_ptr<SceneObjectList> mTargets;
    CallBackT mCallBack;
};

extern std::shared_ptr<AbilityMultitargetObject> Make_AbilityMultitargetObject(
    const std::string& aName,
    size_t aTargetCount,
    std::shared_ptr<RenderingSystem>& aRenderer);
