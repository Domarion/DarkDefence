#include "AnimationSceneSprite.h"

AnimationSceneSprite::AnimationSceneSprite(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :Leaf(aRenderingContext)
    , frame(aRenderingContext)
    , frameNumber(0)
    , oldFrameTime(0)
    , msCount(64)
    , visible(true)
{

}

void AnimationSceneSprite::draw() const
{
    drawAtPosition(getPosition());
}

void AnimationSceneSprite::drawAtPosition(Position pos) const
{
    if (!visible)
        return;

    Position image_position = getRealPosFromLogicPos(pos);

    if (animationStates.size() > 0)
    {
        frame.drawPartAtPosition(image_position, &animationStates.at(currentState).at(frameNumber));
    }
    else
        frame.drawAtPosition(image_position);
}


Size AnimationSceneSprite::getSize() const
{
    return frame.getSize();
}

void AnimationSceneSprite::setSize(Size size)
{
    frame.setSize(size);
}

void AnimationSceneSprite::calculateFrameNumber()
{
    if (oldFrameTime + msCount >= SDL_GetTicks() || animationStates.empty())
        return;

    oldFrameTime = SDL_GetTicks();

    ++frameNumber;

    if (frameNumber >= animationStates.at(currentState).size())
    {
        frameNumber = 0;
    }
}

std::string AnimationSceneSprite::getCurrentState() const
{
    return currentState;

}

void AnimationSceneSprite::setCurrentState(const std::string &value)
{
    currentState = value;

}

void AnimationSceneSprite::setAnimRects(std::string state, vector<SDL_Rect> rects)
{
    setCurrentState(state);
    animationStates[state] = rects;
}

bool AnimationSceneSprite::isVisible() const
{
    return visible;

}

void AnimationSceneSprite::setVisible(bool aVisible)
{
    visible = aVisible;
}

void AnimationSceneSprite::loadTexture(const std::string &path)
{
    frame.loadTexture(path);
}

void AnimationSceneSprite::setSizeFromTexture()
{
    frame.scaleToTexture();
}

void AnimationSceneSprite::setAnchorPointPlace(Enums::AnchorCoordTypes aXCoordAnchorType, Enums::AnchorCoordTypes aYCoordAnchorType)
{
    xCoordAnchorType = aXCoordAnchorType;
    yCoordAnchorType = aYCoordAnchorType;
}

Position AnimationSceneSprite::getRealPosition() const
{
    return getRealPosFromLogicPos(getPosition());
}

Position AnimationSceneSprite::getRealPosFromLogicPos(Position aLogicPos) const
{
    int x = aLogicPos.x - Enums::toIntegralType(xCoordAnchorType) / 2 * getSize().width;
    int y = aLogicPos.y - Enums::toIntegralType(yCoordAnchorType) / 2 * getSize().height;

    return Position{x, y};
}
