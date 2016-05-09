#pragma once
#include "../Sprite.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;
class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite();
    virtual ~AnimatedSprite();
    // CTexture interface
public:
    virtual void draw() override;
    string getCurrentState() const;
    void setCurrentState(const string &value);
    void setAnimRects(string state, vector<SDL_Rect> rects);
private:
    void calculateFrameNumber();
    int frameNumber;
    long oldFrameTime;
    int  msCount;
    map<string, vector<SDL_Rect> > animationStates;
    string currentState;
};

