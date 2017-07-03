#include "AnimationSceneSprite.h"

AnimationSceneSprite::AnimationSceneSprite(std::shared_ptr<RenderingSystem>& aRenderingContext, Animation&& aAnimation)
    : Leaf(aRenderingContext)
    , frame(aRenderingContext)
    , visible(true)
    , flippingFlags(SDL_FLIP_NONE)
    , mAnimation(std::move(aAnimation))
{
}

AnimationSceneSprite::AnimationSceneSprite(std::shared_ptr<RenderingSystem>& aRenderingContext)
    : Leaf(aRenderingContext)
    , frame(aRenderingContext)
    , visible(true)
    , flippingFlags(SDL_FLIP_NONE)
{
}

void AnimationSceneSprite::draw() const
{
    drawAtPosition(getPosition());
}

void AnimationSceneSprite::drawAtPosition(Position pos) const
{
    if (!visible)
    {
        return;
    }

    Position image_position = getRealPosFromLogicPos(pos);

    if (mAnimation.hasAnimations())
    {
        frame.drawScaledPartAtPositionFlipping(
            image_position, frame.getSize(), mAnimation.getCurrentRect(), flippingFlags);
    }
    else
    {
        frame.drawAtPosition(image_position);
    }
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
    mAnimation.calculateFrameNumber();
}

const std::string& AnimationSceneSprite::getCurrentState() const
{
    return mAnimation.getCurrentState();
}

void AnimationSceneSprite::setCurrentState(const std::string& aStateName)
{
    mAnimation.setCurrentState(aStateName);
}

bool AnimationSceneSprite::isVisible() const
{
    return visible;
}

void AnimationSceneSprite::setVisible(bool aVisible)
{
    visible = aVisible;
}

void AnimationSceneSprite::loadTexture(const std::string& aPath)
{
    frame.loadTexture(aPath);
}

void AnimationSceneSprite::setTexture(const Texture2D& aTexture)
{
    frame = aTexture;
}

void AnimationSceneSprite::setSizeFromTexture()
{
    frame.scaleToTexture();
}

void AnimationSceneSprite::setAnchorPointPlace(
    Enums::AnchorCoordTypes aXCoordAnchorType,
    Enums::AnchorCoordTypes aYCoordAnchorType)
{
    xCoordAnchorType = aXCoordAnchorType;
    yCoordAnchorType = aYCoordAnchorType;
}

std::pair<Enums::AnchorCoordTypes, Enums::AnchorCoordTypes>
AnimationSceneSprite::getAnchorPoint() const
{
    return std::make_pair(xCoordAnchorType, yCoordAnchorType);
}

Position AnimationSceneSprite::getRealPosition() const
{
    return getRealPosFromLogicPos(getPosition());
}

void AnimationSceneSprite::setFlipping(int aFlipFlags)
{
    flippingFlags = aFlipFlags;
}

Position
AnimationSceneSprite::getRealPosFromLogicPos(Position aLogicPos) const
{
    int x =
        aLogicPos.x - static_cast<int>(Enums::toIntegralType(xCoordAnchorType) /
                                       2.0 * getSize().width);
    int y =
        aLogicPos.y - static_cast<int>(Enums::toIntegralType(yCoordAnchorType) /
                                       2.0 * getSize().height);

    return Position{x, y};
}
