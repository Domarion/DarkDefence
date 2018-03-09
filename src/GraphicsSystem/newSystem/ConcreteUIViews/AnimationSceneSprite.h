#pragma once

#include <map>
#include <string>
#include <vector>

#include "../Leaf.h"
#include "../Texture2D.h"
#include "Enums.h"

using std::map;
using std::string;
using std::vector;

class AnimationSceneSprite final: public Leaf
{
public:
    class Animation final
    {
    public:

        Animation(const std::map<string, vector<SDL_Rect>>& aAnimationStates);
        Animation() = default;

        void calculateFrameNumber();
        void setCurrentState(const std::string& aStateName);
        bool hasState(const std::string& aStateName);
        bool hasAnimations() const;
        void setAnimRects(const std::string& aState, const std::vector<SDL_Rect>& aRects);

        const SDL_Rect* getCurrentRect() const;
        const std::string& getCurrentState() const;

    private:
        void setDefaultState();

        size_t mFrameNumber {};
        int64_t mOldFrameTime {};
        int16_t mMsCount {64}; //Откуда 64?
        std::map<string, vector<SDL_Rect>> mAnimationStates;
        string mCurrentState;
    };

    explicit AnimationSceneSprite(std::shared_ptr<RenderingSystem>& aRenderingContext, Animation&& aAnimation);

    explicit AnimationSceneSprite(std::shared_ptr<RenderingSystem>& aRenderingContext);
    AnimationSceneSprite() = default;
    virtual ~AnimationSceneSprite() = default;

    // IComposite interface
    virtual void draw() const override;
    void drawAtPosition(Position pos) const;
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
    void calculateFrameNumber();
    const std::string& getCurrentState() const;
    void setCurrentState(const string& value);
    bool isVisible() const;
    void setVisible(bool aVisible);
    void loadTexture(const std::string& aPath);
    void setTexture(const Texture2D& aTexture);
    void setSizeFromTexture();
    void setAnchorPointPlace(Enums::AnchorCoordTypes aXCoordAnchorType, Enums::AnchorCoordTypes aYCoordAnchorType);
    std::pair<Enums::AnchorCoordTypes, Enums::AnchorCoordTypes> getAnchorPoint() const;
    Position getRealPosition() const;
    void setFlipping(int aFlipFlags);
    void setRotation(double aAngle, Position aCenter);

    bool hasRotation() const;
private:

    Position getRealPosFromLogicPos(Position aLogicPos) const;
    Texture2D frame;
    bool visible = true;
    int flippingFlags = SDL_FLIP_NONE;
    double mAngle = 0.0;
    Position mRotationCenter;
    Enums::AnchorCoordTypes xCoordAnchorType = Enums::AnchorCoordTypes::Min;
    Enums::AnchorCoordTypes yCoordAnchorType = Enums::AnchorCoordTypes::Min;
    Animation mAnimation;
};
