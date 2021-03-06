#pragma once

#include <SDL_rect.h>

#include "UtilityStructs.h"

class Camera2D
{
public:
    Camera2D(Size aCameraSize);
    Position getWorldPosition() const;
    void setWorldPosition(Position worldPosition);
    void resetWorldPosition();

    Size getCameraSize() const;
    void setCameraSize(Size cameraSize);
    SDL_Rect* getIntersection(Position aPos, Size aSize) const;
    bool hasIntersection(Position aPos, Size aSize) const;
    Position worldToCameraPosition(Position aWorldPos) const;
    Position screenToWorldPosition(Position aScreenPos) const;

private:
    Position mWorldPosition;
    Size mCameraSize;
};
