#pragma once
#include "CompositeLabel.h"
#include "../../MissionSystem/Mission.h"
#include <list>
using std::list;

#include "../CFont.h"


class MissionView: public CTexture
{
public:
    MissionView();
    virtual ~MissionView();
    void init(Mission& missionRef, std::shared_ptr<CFont> arialFont);
    virtual void draw() override;

private:
    Label missionName;
    Label missionDescription;
    list<CompositeLabel*> missionGoals;
    list<CompositeLabel*> rewardList;
};

