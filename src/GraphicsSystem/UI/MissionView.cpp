#include "MissionView.h"
#include "../../GlobalScripts/Renderer.h"
#include "../../MissionSystem/ResourceGoal.h"

MissionView::MissionView()
    //:arialFont(new CFont() )
{

}

MissionView::~MissionView()
{
    for( auto rewardLabel = rewardList.begin(); rewardLabel != rewardList.end(); ++rewardLabel)
        if (*rewardLabel != nullptr)
            delete *rewardLabel;
    for( auto missionGoalLabel = missionGoals.begin(); missionGoalLabel != missionGoals.end(); ++missionGoalLabel)
        if (*missionGoalLabel != nullptr)
            delete *missionGoalLabel;

}

void MissionView::init(Mission& missionRef, std::shared_ptr<CFont> arialFont)
{
    //arialFont.get()->loadFromFile("Fonts/arial.ttf", 22);

    setRect(0,0, 400, Renderer::getInstance()->getScreenHeight()- 50 );
    loadTexture("GameData/textures/mosaic.png");




    int y = 0;
    missionName.setFont(arialFont);
    missionName.setRect(0, y, 100, 50);
    missionName.setText(missionRef.getCaption());
    y += 60;
    missionDescription.setFont(arialFont);
    missionDescription.setRect(0, y, 200, 50);
    missionDescription.setText(missionRef.getDescription());
    y += 60;

    GameModel::getInstance()->getResourcesModel()->loadFromFile("GameData/resources.txt");

    int x = 0;
    //list<string> goalsStrings = missionRef.getGoalsNeeded();
    list<BasicGoal*> goals = missionRef.getGoals();
    for(auto goal = goals.begin(); goal != goals.end(); ++goal)
    {
        CompositeLabel* temp = new CompositeLabel();
        temp->setFont(arialFont);
        string str = "none";
        if (*goal != nullptr)
        {
            ResourceGoal* resGoal = dynamic_cast<ResourceGoal*>(*goal);
            if (resGoal != nullptr)
            {
                str = "GameData/textures/Resources/"
                        + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(resGoal->getResourceType()) + ".png";
            }

        }

        string needed = std::to_string((*goal)->getNeeded());
        temp->loadIcon(str);
        temp->setIconRect(0, 0, 30, 30);
        temp->setPos(x, y);
        temp->setText(needed);
        missionGoals.push_back(temp);
        y += 60;
    }
    goals.clear();
    x = 0;

    list<string> rewardStrings = missionRef.getReward().getFullDescription();
    for(auto str = rewardStrings.begin(); str != rewardStrings.end(); ++str)
    {
        CompositeLabel* temp = new CompositeLabel();
        temp->setFont(arialFont);
        string iconPath = "GameData/textures/items/" + *str + ".png";
        temp->loadIcon(iconPath);
        temp->setIconRect(0, 0, 30, 30);
        temp->setPos(x, y);
        temp->setText(*str);
        rewardList.push_back(temp);
        y += 60;
    }
    rewardStrings.clear();

    CompositeLabel* temp2 = new CompositeLabel();
    temp2->setFont(arialFont);
    string iconPath2 = "GameData/textures/Resources/Gold.png";
    temp2->loadIcon(iconPath2);
    temp2->setIconRect(0, 0, 30, 30);
    temp2->setPos(x, y);
    string rewardCoins = std::to_string(missionRef.getReward().getGoldCoins());
    temp2->setText(rewardCoins);
    rewardList.push_back(temp2);


}

void MissionView::draw()
{
    CTexture::draw();
    missionName.draw();
    missionDescription.draw();
    for(auto lst = missionGoals.begin(); lst != missionGoals.end(); ++lst)
        (*lst)->draw();
    for(auto lst2 = rewardList.begin(); lst2 != rewardList.end(); ++lst2)
        (*lst2)->draw();

}

