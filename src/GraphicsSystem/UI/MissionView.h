#pragma once
#include "CompositeLabel.h"
#include "../../MissionSystem/Mission.h"
#include <list>
#include <SDL_ttf.h>
using std::list;

class MissionView: public CTexture
{
public:
    MissionView();
    virtual ~MissionView();
    void init(Mission& missionRef);
    virtual void draw() override;
    TTF_Font*  getFont();
private:
    Label missionName;
    Label missionDescription;
    list<CompositeLabel*> missionGoals;
    list<CompositeLabel*> rewardList;
    CFont arialFont;
};

