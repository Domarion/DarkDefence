#pragma once

#include "HeroInventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UISlotContainer.h"

class HeroInventoryController
{
public:
	virtual ~HeroInventoryController();

    void initView(std::shared_ptr<RenderingSystem>& aRenderer);
    void initLocalPositions(Size aRectSize);

    void setView(const std::shared_ptr<UISlotContainer>& aNewView);
    const std::shared_ptr<UISlotContainer>& getView() const;

    void setModel(const std::shared_ptr<HeroInventory>& aNewModel);
    const std::shared_ptr<HeroInventory>& getModel() const;

    void receiveItemFromModel(std::string aCaption, size_t aItemType);

private:

    std::shared_ptr<HeroInventory> mModel;
    std::shared_ptr<UISlotContainer> mView;
    std::vector<Position> mSlotsPositions;
};


