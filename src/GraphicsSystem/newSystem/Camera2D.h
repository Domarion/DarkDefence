#pragma once

#include "UtilityStructs.h"
#include <SDL_rect.h>

class Camera2D
{
public:
    Camera2D(Size aCameraSize);
    Position getWorldPosition() const;
    void setWorldPosition(Position worldPosition);

    Size getCameraSize() const;
    void setCameraSize(Size cameraSize);
    SDL_Rect* getIntersection(Position aPos, Size aSize) const;
    bool hasIntersection(Position aPos, Size aSize) const;
    Position worldToCameraPosition(Position aWorldPos) const;
private:
    Position mWorldPosition;
    Size mCameraSize;
};
