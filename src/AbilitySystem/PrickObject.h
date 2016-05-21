#pragma once
#include "../Grouping/SceneObject.h"

class PrickObject: public SceneObject
{
public:
    PrickObject(int aDamage);
    virtual ~PrickObject();

    // SceneObject interface
public:
    virtual void init() override;
    virtual bool update(double timestep) override;
    virtual void finalize() override;

private:
    bool notDid;
    int damage;
};
