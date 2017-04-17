#pragma once
#include "../Leaf.h"
#include "../Texture2D.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "Enums.h"

class AnimationSceneSprite final: public Leaf
{
public:
    explicit AnimationSceneSprite(std::shared_ptr<RenderingSystem>& aRenderingContext);
    AnimationSceneSprite() = default;
    virtual ~AnimationSceneSprite() = default;

    // IComposite interface
public:
    virtual void draw() const override;
    void drawAtPosition(Position pos) const;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
    void calculateFrameNumber();
    string getCurrentState() const;
    void setCurrentState(const string &value);
    void setAnimRects(string state, vector<SDL_Rect> rects);
    bool isVisible() const;
    void setVisible(bool aVisible);
    void loadTexture(const std::string& path);
    void setTexture(const Texture2D& aTexture);
    void setSizeFromTexture();
    void setAnchorPointPlace(Enums::AnchorCoordTypes aXCoordAnchorType, Enums::AnchorCoordTypes aYCoordAnchorType);
    Position getRealPosition() const;
    void setFlipping(int aFlipFlags);
private:
    Position getRealPosFromLogicPos(Position aLogicPos) const;
    Texture2D frame;
    size_t frameNumber;
    long oldFrameTime;
    int  msCount;
    std::map<string, vector<SDL_Rect> > animationStates;
    string currentState;
    bool visible;
    int flippingFlags;
    Enums::AnchorCoordTypes xCoordAnchorType = Enums::AnchorCoordTypes::Min;
    Enums::AnchorCoordTypes yCoordAnchorType = Enums::AnchorCoordTypes::Min;

};
