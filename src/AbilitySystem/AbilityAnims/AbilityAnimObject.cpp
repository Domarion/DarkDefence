#include "AbilityAnimObject.hpp"

AbilityAnimObject::AbilityAnimObject(double timeToLiveSec)
    : SceneObject()
    , mTimeToLive(timeToLiveSec)
{

}

bool AbilityAnimObject::update(double timestep)
{
    if (mTimeToLive < 0)
    {
        return false;
    }

    mTimeToLive -= timestep;
    return SceneObject::update(timestep);
;
}
