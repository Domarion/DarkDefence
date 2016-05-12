#include "MissionView.h"
#include "../../GlobalScripts/Renderer.h"
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

    int x = 0;
    list<string> goalsStrings = missionRef.getGoalsFullDesc();
    for(auto str = goalsStrings.begin(); str != goalsStrings.end(); ++str)
    {
        Label* temp = new Label();
        temp->setFont(arialFont, arialFontColor);
        temp->setRect(x, y, 200, 50);
        temp->setText(*str);
        missionGoals.push_back(temp);
        y += 60;
    }


    x = 0;

    list<string> rewardStrings = missionRef.getReward().getFullDescription();
    for(auto str = rewardStrings.begin(); str != rewardStrings.end(); ++str)
    {
        Label* temp = new Label(*str);
        temp->setFont(arialFont, arialFontColor);
        temp->setRect(x, y, 150, 50);
        temp->setText(*str);
        rewardList.push_back(temp);
        y += 60;
    }



}

void MissionView::draw()
{
    missionName.draw();
    missionDescription.draw();
    for(auto lst = missionGoals.begin(); lst != missionGoals.end(); ++lst)
        (*lst)->draw();
    for(auto lst2 = rewardList.begin(); lst2 != rewardList.end(); ++lst2)
        (*lst2)->draw();

}

TTF_Font * const MissionView::getFont()
{
    return arialFont;

}
