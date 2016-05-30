#include "AnimatedSprite.h"
#include "../../GlobalScripts/Renderer.h"
AnimatedSprite::AnimatedSprite()
    :frameNumber(0), oldFrameTime(0), msCount(64)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::draw()
{
    if (animationStates.size() > 0)
    {
        calculateFrameNumber();
        Renderer::getInstance()->renderTexture(getTexture(),getRect().x, getRect().y, 0, 0, &animationStates.at(currentState).at(frameNumber));
    }
    else
       CTexture::draw();
}

void AnimatedSprite::calculateFrameNumber()
{
    if (oldFrameTime + msCount >= SDL_GetTicks())
        return;
    oldFrameTime = SDL_GetTicks();

    ++frameNumber;

    if (frameNumber >= animationStates.at(currentState).size())
    {
        frameNumber = 0;
    }
}

string AnimatedSprite::getCurrentState() const
{
    return currentState;
}

void AnimatedSprite::setCurrentState(const string &value)
{
    currentState = value;
}

void AnimatedSprite::setAnimRects(string state, vector<SDL_Rect> rects)
{
    setCurrentState(state);
    animationStates[state] = rects;
}
