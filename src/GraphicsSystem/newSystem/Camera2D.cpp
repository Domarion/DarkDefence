#include "Camera2D.h"

Camera2D::Camera2D(Size aCameraSize)
    : mWorldPosition()
    , mCameraSize(aCameraSize)
{
}

Position Camera2D::getWorldPosition() const
{
    return mWorldPosition;
}

void Camera2D::setWorldPosition(Position worldPosition)
{
    mWorldPosition = worldPosition;
}

void Camera2D::resetWorldPosition()
{
    mWorldPosition = Position::Zero();
}

Size Camera2D::getCameraSize() const
{
    return mCameraSize;
}

void Camera2D::setCameraSize(Size cameraSize)
{
    mCameraSize = cameraSize;
}

SDL_Rect* Camera2D::getIntersection(Position aPos, Size aSize) const
{
    SDL_Rect objRect{aPos.x, aPos.y, aSize.width, aSize.height};
    SDL_Rect cameraRect{mWorldPosition.x, mWorldPosition.y, mCameraSize.width, mCameraSize.height};
    SDL_Rect* intersectionRect = new SDL_Rect();
    SDL_IntersectRect(&objRect, &cameraRect, intersectionRect);

    return intersectionRect;
}

bool Camera2D::hasIntersection(Position aPos, Size aSize) const
{
    SDL_Rect objRect{aPos.x, aPos.y, aSize.width, aSize.height};
    SDL_Rect cameraRect{mWorldPosition.x, mWorldPosition.y, mCameraSize.width, mCameraSize.height};
    return SDL_HasIntersection(&objRect, &cameraRect);
}

Position Camera2D::worldToCameraPosition(Position aWorldPos) const
{
    return aWorldPos - mWorldPosition;
}

Position Camera2D::screenToWorldPosition(Position aScreenPos) const
{
    return aScreenPos + mWorldPosition;
}
