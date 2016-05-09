#pragma once
#include "../Grouping/SceneObject.h"

class PrickObject: public SceneObject
{
public:
    PrickObject();
    virtual ~PrickObject();

    // SceneObject interface
public:
    virtual void init() override;
    virtual bool update(double timestep) override;
    virtual void finalize() override;

private:
    bool notDid;
};
