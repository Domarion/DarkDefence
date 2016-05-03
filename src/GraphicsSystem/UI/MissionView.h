#pragma once
#include "Label.h"
#include "../../MissionSystem/Mission.h"
#include <list>
#include <SDL2/SDL_ttf.h>
using std::list;

class MissionView: public CTexture
{
public:
    MissionView();
    virtual ~MissionView();
    void init(Mission& missionRef);
    virtual void draw() override;
    TTF_Font* const getFont();
private:
    Label missionName;
    Label missionDescription;
    list<Label*> missionGoals;
    list<Label*> rewardList;
    TTF_Font* arialFont;
};

