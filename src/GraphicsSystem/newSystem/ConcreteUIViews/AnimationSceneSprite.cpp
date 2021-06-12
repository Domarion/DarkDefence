#include <limits>

#include "AnimationSceneSprite.h"

size_t ObjectWithId::allObjectId = 0;

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
        return;
    }

    if (!hasRotation())
    {
        SDL_RendererFlip flags = static_cast<SDL_RendererFlip>(flippingFlags);

        frame.drawAtPositionFlipped(image_position, flags);
        return;
    }

    frame.drawAtPositionRotated(image_position, mAngle, mRotationCenter);
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

void AnimationSceneSprite::setRotation(double aAngle, Position aCenter)
{
    mAngle = aAngle;
    mRotationCenter = aCenter;
}

bool AnimationSceneSprite::hasRotation() const
{
    return fabs(mAngle) > std::numeric_limits<double>::epsilon();
}

Position AnimationSceneSprite::getRealPosFromLogicPos(Position aLogicPos) const
{
    int x = aLogicPos.x - static_cast<int>(Enums::toIntegralType(xCoordAnchorType) / 2.0 * getSize().width);
    int y = aLogicPos.y - static_cast<int>(Enums::toIntegralType(yCoordAnchorType) / 2.0 * getSize().height);

    return Position{x, y};
}

AnimationSceneSprite::Animation::Animation(const std::map<std::string, vector<SDL_Rect> >& aAnimationStates)
    : mAnimationStates(aAnimationStates)
{
    setDefaultState();
}

void AnimationSceneSprite::Animation::calculateFrameNumber()
{
    if (mOldFrameTime + mMsCount >= SDL_GetTicks() || mAnimationStates.empty())
    {
        return;
    }

    mOldFrameTime = SDL_GetTicks();

    ++mFrameNumber;

    if (mFrameNumber >= mAnimationStates.at(mCurrentState).size())
    {
        mFrameNumber = 0;
    }
}

void AnimationSceneSprite::Animation::setCurrentState(const std::string& aStateName)
{
    if (hasState(aStateName))
    {
        mCurrentState = aStateName;
        mFrameNumber = 0;
    }
}

bool AnimationSceneSprite::Animation::hasState(const std::string& aStateName)
{
    if (aStateName.empty())
    {
        return false;
    }

    return mAnimationStates.find(aStateName) != mAnimationStates.cend();
}

bool AnimationSceneSprite::Animation::hasAnimations() const
{
    return !mAnimationStates.empty();
}

void AnimationSceneSprite::Animation::setAnimRects(const std::string& aState, const std::vector<SDL_Rect>& aRects)
{
    mAnimationStates[aState] = aRects;
    //TODO инициализировать правильным состоянием анимации
    setCurrentState(aState);
}

const SDL_Rect*AnimationSceneSprite::Animation::getCurrentRect() const
{
    return &mAnimationStates.at(mCurrentState).at(mFrameNumber);
}

const std::string&AnimationSceneSprite::Animation::getCurrentState() const
{
    return mCurrentState;
}

void AnimationSceneSprite::Animation::setDefaultState()
{
    if (mAnimationStates.empty())
    {
        return;
    }

    mCurrentState = mAnimationStates.cbegin()->first;
    mFrameNumber = 0;
}

void ObjectWithId::resetObjectIds()
{
    allObjectId = 0;
}
