#pragma once

#include "../Grouping/Scene.h"
#include "../ItemSystem/InventoryController.h"
#include "../ItemSystem/HeroInventoryController.h"

class InventoryScene: public Scene
{
public:
    InventoryScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);

    virtual void init() override;
    virtual void clear() override;

private:
    void initControlButton();
    void initHeroView();
    void initInventoryView();
    void inventoryDescription(const std::shared_ptr<ConcreteComposite>& aDescComposite);
    std::unique_ptr<InventoryController> inventoryController;
    std::unique_ptr<HeroInventoryController> heroController;
    std::shared_ptr<ConcreteComposite> descView;
};

