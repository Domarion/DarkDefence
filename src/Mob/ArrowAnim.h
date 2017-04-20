#pragma once
#include "../Grouping/SceneObject.h"

class ArrowAnim : public SceneObject
{
public:
    explicit ArrowAnim(Position aTargetPosition);
    virtual ~ArrowAnim() = default;

    bool update(double timestep) override;
private:
    bool ReachedPos();
    Position mTargetPosition{};

    int signum(int aValue) const
    {
        if (aValue == 0)
            return 0;

        return aValue > 0 ? 1 : -1;
    }
};
