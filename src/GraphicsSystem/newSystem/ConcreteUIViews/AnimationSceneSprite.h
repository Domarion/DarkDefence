#pragma once
#include "../Leaf.h"
#include "../Texture2D.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;
class AnimationSceneSprite final: public Leaf
{
public:
    explicit AnimationSceneSprite(std::shared_ptr<RenderingSystem>& aRenderingContext);
    AnimationSceneSprite() = default;
    virtual ~AnimationSceneSprite() = default;
    // IComposite interface
public:
    virtual void draw() const override;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
    void calculateFrameNumber();
    string getCurrentState() const;
    void setCurrentState(const string &value);
    void setAnimRects(string state, vector<SDL_Rect> rects);
    bool isVisible() const;
    void setVisible(bool aVisible);
    void loadTexture(const std::string& path);
private:
    Texture2D frame;
    size_t frameNumber;
    long oldFrameTime;
    int  msCount;
    std::map<string, vector<SDL_Rect> > animationStates;
    string currentState;
    bool visible;
};
