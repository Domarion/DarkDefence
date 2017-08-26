#pragma once
#include "../UIElement/ConcreteComposite.h"
#include "../../../MissionSystem/Mission.h"
#include "../Font.h"
class UIMissionView final: public ConcreteComposite
{
public:
    explicit UIMissionView(
        std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout);
    void init(Mission& aMission, Font& aFont);

private:
    void initGoals(Mission& aMission, Font& aFont);
    void initRewards(Mission& aMission, Font& aFont);
};
