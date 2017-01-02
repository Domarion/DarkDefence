#include "UIMissionView.h"
#include "../UIElement/UILabel.h"
#include "../UIElement/UIImage.h"
#include "../../../MissionSystem/ResourceGoal.h"
#include "GlobalScripts/GameModel.h"

UIMissionView::UIMissionView(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :ConcreteComposite(aRenderingContext)
{

}

void UIMissionView::init(Mission &aMission, Font &aFont)
{

    auto missionBackGroundImage = std::make_shared<UIImage>(renderer);
    missionBackGroundImage->loadTexture("GameData/textures/mosaic.png");
    missionBackGroundImage->setSize(this->getSize());
    addChild(missionBackGroundImage);


    auto missionNameLabel = std::make_shared<UILabel>(aMission.getCaption(), aFont, renderer);
   // missionNameLabel->setSize(Size(100, 50));
    addChild(missionNameLabel);

    auto missionDescriptionLabel = std::make_shared<UILabel>(aMission.getDescription(), aFont, renderer);
    //missionDescriptionLabel->setSize(Size(200, 50));
    missionDescriptionLabel->setPosition(getNextVerticalPosition());

    addChild(missionDescriptionLabel);

    initGoals(aMission, aFont);
    initRewards(aMission, aFont);
}

void UIMissionView::initGoals(Mission &aMission, Font &aFont)
{
    auto missionGoalsGroup = std::make_shared<ConcreteComposite>(renderer);
    missionGoalsGroup->setPosition(getNextVerticalPosition());
    missionGoalsGroup->setSize(Size(this->getSize().width, this->getSize().height/4));

    list<std::shared_ptr<BasicGoal>> goals = aMission.getGoals();
    for(auto& goal : goals)
    {
        if (goal != nullptr)
        {
            std::shared_ptr<ResourceGoal> resGoal = std::dynamic_pointer_cast<ResourceGoal>(goal);
//            ResourceGoal* resGoal = dynamic_cast<ResourceGoal*>(goal.get());
            if (resGoal != nullptr)
            {
                auto missionGoalIcon = std::make_shared<UIImage>(renderer);
                missionGoalIcon->setSize(Size(48, 48));
                string iconFilePath = "GameData/textures/Resources/"
                        + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(static_cast<int>(resGoal->getResourceType())) + ".png";
                missionGoalIcon->loadTexture(iconFilePath);
                missionGoalsGroup->addChild(missionGoalIcon);


                string needed = std::to_string(goal->getNeeded());
                auto missionGoalLabel = std::make_shared<UILabel>(needed, aFont, renderer);
                missionGoalLabel->setPosition(missionGoalsGroup->getNextHorizontalPosition());

                missionGoalsGroup->addChild(missionGoalLabel);

            }
        }
    }
    goals.clear();
    addChild(missionGoalsGroup);
}

void UIMissionView::initRewards(Mission &aMission, Font &aFont)
{
    auto missionRewardsGroup = std::make_shared<ConcreteComposite>(renderer);
    missionRewardsGroup->setPosition(getNextVerticalPosition());
    missionRewardsGroup->setSize(Size(this->getSize().width, this->getSize().height/4));

    list<string> rewardStrings = aMission.getReward().getFullDescription();
    for(auto& descString : rewardStrings)
    {

        Position pos = missionRewardsGroup->getNextVerticalPosition();
        auto missionRewardIcon = std::make_shared<UIImage>(renderer);
        missionRewardIcon->setSize(Size(48, 48));
        missionRewardIcon->setPosition(pos);
        string iconFilePath = "GameData/textures/items/" + descString + ".png";
        missionRewardIcon->loadTexture(iconFilePath);

        missionRewardsGroup->addChild(missionRewardIcon);


        Position labelPos (missionRewardsGroup->getNextHorizontalPosition().x, pos.y);

        auto missionRewardLabel = std::make_shared<UILabel>(descString, aFont, renderer);
        missionRewardLabel->setPosition(labelPos);

        missionRewardsGroup->addChild(missionRewardLabel);
    }
    rewardStrings.clear();

    Position goldIconPos = missionRewardsGroup->getNextVerticalPosition();
    auto missionRewardGoldIcon = std::make_shared<UIImage>(renderer);
    missionRewardGoldIcon->setSize(Size(48, 48));
    missionRewardGoldIcon->setPosition(goldIconPos);
    string goldIconFilePath = "GameData/textures/Resources/Gold.png";
    missionRewardGoldIcon->loadTexture(goldIconFilePath);

    missionRewardsGroup->addChild(missionRewardGoldIcon);


    Position labelGoldPos (missionRewardsGroup->getNextHorizontalPosition().x, goldIconPos.y);
    string rewardCoins = std::to_string(aMission.getReward().getGoldCoins());

    auto missionRewardGoldLabel = std::make_shared<UILabel>(rewardCoins, aFont, renderer);
    missionRewardGoldLabel->setPosition(labelGoldPos);

    missionRewardsGroup->addChild(missionRewardGoldLabel);


    addChild(missionRewardsGroup);
}
