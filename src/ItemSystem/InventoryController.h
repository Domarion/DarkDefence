#pragma once

#include <memory>

#include "Inventory.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
#include "../GraphicsSystem/newSystem/IComposite.h"
#include "../GraphicsSystem/newSystem/Font.h"
#include "../GraphicsSystem/newSystem/StubLayout.h"

class InventoryController
{
public:
    explicit InventoryController(std::shared_ptr<RenderingSystem>& aRenderer);
    virtual ~InventoryController() = default;
    void setView(std::shared_ptr<UIScrollList>& newView);
    void setModel(std::shared_ptr<Inventory> newModel);
    std::shared_ptr<Inventory> getModel() const;
    void initView();
    void receiveItemFromModel(string aCaption, size_t itemType);
    bool sendItemToModel(int index);

private:
    void addItemView(
        const std::string& aItemCaption,
        const std::string& aItemDescription,
        const std::shared_ptr<StubLayout>& aLayout,
        const Font& aFont);
    std::shared_ptr<Inventory> model;
    std::shared_ptr<UIScrollList> view;
    std::shared_ptr<RenderingSystem> renderer;

    Font arial;
    vector<std::shared_ptr<IComposite>> buttons;
};

