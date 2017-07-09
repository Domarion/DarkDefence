#pragma once

#include "../Grouping/SceneObject.h"

class ArrowAnim : public SceneObject
{
public:
    explicit ArrowAnim(Position aTargetPosition);

    bool update(double timestep) override;

private:

    bool ReachedPos();
    Position mTargetPosition{};
};
