#include "ArrowAnim.h"
#include <limits>

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
    auto signum = [](int aValue) -> int
        {
            if (aValue == 0)
            {
                return 0;
            }

            return aValue > 0 ? 1 : -1;
        };

    Position newMobPos{getRealPosition()};

    int diffX = mTargetPosition.x  - newMobPos.x;
    int diffY = mTargetPosition.y  - newMobPos.y;

    if (diffX == 0 && diffY == 0)
        return true;

    int speed = 5;

    int signumX = signum(diffX);
    int signumY = signum(diffY);

    newMobPos.x += (abs(diffX) < speed)? diffX : signumX * speed;
    newMobPos.y += (abs(diffY) < speed)? diffY : signumY * speed;

    auto& spriteRef = getSprite();
    if (spriteRef)
    {
        if (abs(diffX) > std::numeric_limits<double>::epsilon())
        {
            spriteRef->setRotation(atan(tan(abs(diffY)/abs(diffX))), Position{});
        }
        int flipping = (diffX < 0)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        spriteRef->setFlipping(flipping);
    }


    setPosition(newMobPos);
    return false;
}
