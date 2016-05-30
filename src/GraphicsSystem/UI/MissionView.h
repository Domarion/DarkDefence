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

private:
    Label missionName;
    Label missionDescription;
    list<CompositeLabel*> missionGoals;
    list<CompositeLabel*> rewardList;
    std::shared_ptr<CFont> arialFont;
};

