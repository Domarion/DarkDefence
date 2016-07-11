#pragma once
#include "../CTexture.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;

class AnimatedSprite : public CTexture
{
public:
    AnimatedSprite();
    virtual ~AnimatedSprite();
    // CTexture interface
public:
    virtual void draw() override;
    void calculateFrameNumber();
    string getCurrentState() const;
    void setCurrentState(const string &value);
    void setAnimRects(string state, vector<SDL_Rect> rects);
private:

    size_t frameNumber;
    long oldFrameTime;
    int  msCount;
    map<string, vector<SDL_Rect> > animationStates;
    string currentState;
};

