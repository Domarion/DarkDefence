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

    if (diffX == 0 && diffY == 0)
        return true;

    int speed = 5;

    int signumX = signum(diffX);
    int signumY = signum(diffY);
//    std::cout << "signX " << signumX << " signY " << signumY << std::endl;

    newMobPos.x += (abs(diffX) < speed)? diffX : signumX * speed;
    newMobPos.y += (abs(diffY) < speed)? diffY : signumY * speed;


    setPosition(newMobPos);
    return false;
}
