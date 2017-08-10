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
    class Animation final
    {
    public:

        Animation(const std::map<string, vector<SDL_Rect>>& aAnimationStates)
            : mAnimationStates(aAnimationStates)
        {
            setDefaultState();
        }

        Animation() = default;

        void calculateFrameNumber()
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

        void setCurrentState(const std::string& aStateName)
        {
            if (hasState(aStateName))
            {
                mCurrentState = aStateName;
            }
        }

        bool hasState(const std::string& aStateName)
        {
            if (aStateName.empty())
            {
                return false;
            }

            return mAnimationStates.find(aStateName) != mAnimationStates.cend();
        }

        bool hasAnimations() const
        {
            return !mAnimationStates.empty();
        }

        void setAnimRects(const std::string& aState, const std::vector<SDL_Rect>& aRects)

        {
            mAnimationStates[aState] = aRects;
            //TODO инициализировать правильным состоянием анимации
            setCurrentState(aState);
        }

        const SDL_Rect* getCurrentRect() const
        {
            return &mAnimationStates.at(mCurrentState).at(mFrameNumber);
        }
        const std::string& getCurrentState() const
        {
            return mCurrentState;
        }

    private:
        void setDefaultState()
        {
            if (mAnimationStates.empty())
            {
                return;
            }

            mCurrentState = mAnimationStates.cbegin()->first;
        }
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

private:

    Position getRealPosFromLogicPos(Position aLogicPos) const;
    Texture2D frame;
    bool visible;
    int flippingFlags;
    Enums::AnchorCoordTypes xCoordAnchorType = Enums::AnchorCoordTypes::Min;
    Enums::AnchorCoordTypes yCoordAnchorType = Enums::AnchorCoordTypes::Min;
    Animation mAnimation;
};
