#include "UIMissionView.h"
#include "../UIElement/UILabel.h"
#include "../UIElement/UIImage.h"
#include "../../../MissionSystem/ResourceGoal.h"
#include "GlobalScripts/GameModel.h"
#include "GlobalScripts/ResourceManager.h"

UIMissionView::UIMissionView(
    std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout)
    : ConcreteComposite(aRenderingContext, aLayout)
{
}

void UIMissionView::init(Mission& aMission, const Font& aFont)
{
    auto missionNameLabel = std::make_shared<UILabel>(aMission.getCaption(), aFont, renderer);
    addChild(missionNameLabel);

    auto missionDescriptionLabel = std::make_shared<UILabel>(aMission.getDescription(), aFont, renderer);
    missionDescriptionLabel->setPosition(getNextVerticalPosition());

    addChild(missionDescriptionLabel);

    initGoals(aMission, aFont);
    initRewards(aMission, aFont);
}

void UIMissionView::initGoals(Mission &aMission, const Font& aFont)
{
    auto missionGoalsGroup = std::make_shared<ConcreteComposite>(renderer, mLayout);
    missionGoalsGroup->setScalingFactor(getScalingFactor());
    missionGoalsGroup->setSize(Size(this->getSize().width, this->getSize().height/4));
    missionGoalsGroup->setPosition(getNextVerticalPosition());

    list<std::shared_ptr<BasicGoal>> goals = aMission.getGoals();
    for(auto& goal : goals)
    {
        if (goal != nullptr)
        {
            std::shared_ptr<ResourceGoal> resGoal = std::dynamic_pointer_cast<ResourceGoal>(goal);

            if (resGoal != nullptr)
            {
                auto missionLabelWithIcon = std::make_shared<ConcreteComposite>(renderer, mLayout);

                missionLabelWithIcon->setPosition(missionGoalsGroup->getNextVerticalPosition());

                auto missionGoalIcon = std::make_shared<UIImage>(renderer);

                string resourceName =
                    GameModel::getInstance()->getResourcesModel()->getResourceNameFromType(resGoal->getResourceType());

                missionGoalIcon->setTexture(ResourceManager::getInstance()->getTexture(resourceName));

                Size textureSize = missionGoalIcon->getSize();
                missionLabelWithIcon->addChild(missionGoalIcon);

                string needed = std::to_string(goal->getNeeded());
                auto missionGoalLabel = std::make_shared<UILabel>(needed, aFont, renderer);
                missionGoalLabel->setPosition(missionLabelWithIcon->getNextHorizontalPosition());

                missionLabelWithIcon->addChild(missionGoalLabel);

                const auto& missionGoalLabelSize = missionGoalLabel->getSize();

                missionLabelWithIcon->setSize(Size(textureSize.width + missionGoalLabelSize.width, textureSize.height));

                missionGoalsGroup->addChild(missionLabelWithIcon);
            }
        }
    }

    goals.clear();
    addChild(missionGoalsGroup);
}

void UIMissionView::initRewards(Mission &aMission, const Font& aFont)
{
    auto missionRewardsGroup = std::make_shared<ConcreteComposite>(renderer, mLayout);
    missionRewardsGroup->setScalingFactor(getScalingFactor());

    missionRewardsGroup->setPosition(getNextVerticalPosition());
    missionRewardsGroup->setSize(Size(this->getSize().width, this->getSize().height/4));
    const Size iconSize{48, 48};
    list<string> rewardStrings = aMission.getReward().getFullDescription();

    for(auto& descString : rewardStrings)
    {
        Position pos = missionRewardsGroup->getNextVerticalPosition();

        auto missionLabelWithIcon = std::make_shared<ConcreteComposite>(renderer, mLayout);
        missionLabelWithIcon->setPosition(pos);
        auto missionRewardIcon = std::make_shared<UIImage>(renderer);
        missionRewardIcon->setSize(iconSize);

        string iconFilePath = "GameData/textures/items/" + descString + ".png";
        missionRewardIcon->loadTexture(iconFilePath);

        missionLabelWithIcon->addChild(missionRewardIcon);


        Position labelPos = missionLabelWithIcon->getNextHorizontalPosition();

        auto missionRewardLabel = std::make_shared<UILabel>(descString, aFont, renderer);
        missionRewardLabel->setPosition(labelPos);

        missionLabelWithIcon->addChild(missionRewardLabel);

        const auto& missionRewardLabelSize = missionRewardLabel->getSize();

        missionLabelWithIcon->setSize(Size(iconSize.width + missionRewardLabelSize.width, iconSize.height));


        missionRewardsGroup->addChild(missionLabelWithIcon);
    }

    rewardStrings.clear();

    Position goldIconPos = missionRewardsGroup->getNextVerticalPosition();
    auto missionRewardGoldIcon = std::make_shared<UIImage>(renderer);

    missionRewardGoldIcon->setScalingFactor(getScalingFactor());

    missionRewardGoldIcon->setPosition(goldIconPos);
    std::string goldName{"Gold"};
    missionRewardGoldIcon->setTexture(ResourceManager::getInstance()->getTexture(goldName));

    missionRewardsGroup->addChild(missionRewardGoldIcon);

    Position labelGoldPos (missionRewardsGroup->getNextHorizontalPosition().x, goldIconPos.y);
    string rewardCoins = std::to_string(aMission.getReward().getGoldCoins());

    auto missionRewardGoldLabel = std::make_shared<UILabel>(rewardCoins, aFont, renderer);
    missionRewardGoldLabel->setScalingFactor(getScalingFactor());

    missionRewardGoldLabel->setPosition(labelGoldPos);

    missionRewardsGroup->addChild(missionRewardGoldLabel);


    addChild(missionRewardsGroup);
}
