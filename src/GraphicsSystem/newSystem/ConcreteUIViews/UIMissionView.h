#pragma once

#include "../UIElement/ConcreteComposite.h"
#include "../../../MissionSystem/Mission.h"
#include "../Font.h"

class UIMissionView final: public ConcreteComposite
{
public:
    explicit UIMissionView(
        std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout);
    void init(const Mission& aMission, const Font& aFont);

private:
    void initGoals(const Mission& aMission, const Font& aFont);
    void initRewards(const Mission& aMission, const Font& aFont);
};
