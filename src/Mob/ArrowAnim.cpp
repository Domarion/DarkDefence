#include "ArrowAnim.h"

ArrowAnim::ArrowAnim(Position aTargetPosition)
    : SceneObject()
    , mTargetPosition(aTargetPosition)
{
}

bool ArrowAnim::update(double timestep)
{
    if (ReachedPos())
        return false;
    return SceneObject::update(timestep);
}

bool ArrowAnim::ReachedPos()
{
    Position newMobPos{getRealPosition()};

    int diffX = mTargetPosition.x  - newMobPos.x;
    int diffY = mTargetPosition.y  - newMobPos.y;

    std::cout << "arrow Pos " << newMobPos << std::endl;
    std::cout << "targ Pos " << mTargetPosition << std::endl;
    if (diffX == 0 && diffY == 0)
        return true;

    int speed = 5;

    int signumX = signum(diffX);
    int signumY = signum(diffY);
    std::cout << "signX " << signumX << " signY " << signumY << std::endl;

    if (abs(diffX) < speed)
    {
        newMobPos.x += signumX * diffX;
    }
    else
    {
        newMobPos.x += signumX * speed;
    }

    if (abs(diffY) < speed)
    {
        newMobPos.y += signumY * diffY;
    }
    else
    {
        newMobPos.y += signumY * speed;
    }

    setPosition(newMobPos);
    return false;
}
