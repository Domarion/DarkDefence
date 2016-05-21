#include "MissionView.h"
#include "../../GlobalScripts/Renderer.h"
#include "../../MissionSystem/ResourceGoal.h"

MissionView::MissionView()
    :arialFont( nullptr)
{

}

MissionView::~MissionView()
{
    if (arialFont != nullptr)
        TTF_CloseFont(arialFont);
}

void MissionView::init(Mission& missionRef)
{
    arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 22);

    setRect(0,0, 400, 500);
    setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/mosaic.png"));



    SDL_Color arialFontColor = {255, 255, 255};
    int y = 0;
    missionName.setFont(arialFont, arialFontColor);
    missionName.setRect(0, y, 100, 50);
    missionName.setText(missionRef.getCaption());
    y += 60;
    missionDescription.setFont(arialFont, arialFontColor);
    missionDescription.setRect(0, y, 200, 50);
    missionDescription.setText(missionRef.getDescription());
    y += 60;

    GameModel::getInstance()->getResourcesModel()->loadFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/resources.txt");

    int x = 0;
    //list<string> goalsStrings = missionRef.getGoalsNeeded();
    list<BasicGoal*> goals = missionRef.getGoals();
    for(auto goal = goals.begin(); goal != goals.end(); ++goal)
    {
        CompositeLabel* temp = new CompositeLabel();
        temp->setFont(arialFont, arialFontColor);
        string str = "none";
        if (*goal != nullptr)
        {
            ResourceGoal* resGoal = dynamic_cast<ResourceGoal*>(*goal);
            if (resGoal != nullptr)
            {
                str = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/Resources/"
                        + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(resGoal->getResourceType()) + ".png";
            }

        }

        string needed = std::to_string((*goal)->getNeeded());
        temp->setIcon(Renderer::getInstance()->loadTextureFromFile(str));
        temp->setIconRect(0, 0, 30, 30);
        temp->setPos(x, y);
        temp->setText(needed);
        missionGoals.push_back(temp);
        y += 60;
    }

    x = 0;

    list<string> rewardStrings = missionRef.getReward().getFullDescription();
    for(auto str = rewardStrings.begin(); str != rewardStrings.end(); ++str)
    {
        CompositeLabel* temp = new CompositeLabel();
        temp->setFont(arialFont, arialFontColor);
        string iconPath = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/items/" + *str + ".png";
        temp->setIcon(Renderer::getInstance()->loadTextureFromFile(iconPath));
        temp->setIconRect(0, 0, 30, 30);
        temp->setPos(x, y);
        temp->setText(*str);
        rewardList.push_back(temp);
        y += 60;
    }

    CompositeLabel* temp2 = new CompositeLabel();
    temp2->setFont(arialFont, arialFontColor);
    string iconPath2 = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/Resources/Gold.png";
    temp2->setIcon(Renderer::getInstance()->loadTextureFromFile(iconPath2));
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

TTF_Font * MissionView::getFont()
{
    return arialFont;

}
