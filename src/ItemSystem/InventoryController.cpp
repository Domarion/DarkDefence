#include <cassert>

#include "InventoryController.h"
#include "../Grouping/FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../GlobalScripts/ResourceManager.h"
#include "../Logging/Logger.h"

InventoryController::InventoryController(std::shared_ptr<RenderingSystem>& aRenderer)
    : renderer(aRenderer)
{
}

void InventoryController::setView(std::shared_ptr<UIScrollList>& newView)
{
	view = newView;
}

void InventoryController::setModel(std::shared_ptr<Inventory> newModel)
{
	model = newModel;
}

std::shared_ptr<Inventory> InventoryController::getModel() const
{
	return model;
}

void InventoryController::initView()
{
    arial.loadFromFile("Fonts/arial.ttf", 20);

    view->ConnectMethod(std::bind(&InventoryController::sendItemToModel, this, std::placeholders::_1));
    model->ConnectControllerReceiver(
        std::bind(&InventoryController::receiveItemFromModel, this, std::placeholders::_1, std::placeholders::_2));

	int count = model->getItemCount();
	if (count == 0)
		return;

    auto layout = std::make_shared<StubLayout>();
    const auto& fontRef =  FontManager::getInstance()->getFontByKind2("ButtonFont");

    for (int i = 0; i != count; ++i)
	{
        auto itemPtr = model->getItemFromIndex(i);
        addItemView(itemPtr->getCaption(), itemPtr->getDescription(), layout, fontRef);
	}
}

void InventoryController::receiveItemFromModel(string aCaption, size_t /*itemType*/)
{
    if (aCaption.empty())
        return;

    const Font& fontRef = FontManager::getInstance()->getFontByKind2("ButtonFont");
    auto layout = std::make_shared<StubLayout>();

    addItemView(aCaption, "TODO: desc stub", layout, fontRef);
}

bool InventoryController::sendItemToModel(int index)
{
    return model->sendItem(index);
}

void InventoryController::addItemView(
    const std::string& aItemCaption,
    const std::string& aItemDescription,
    const std::shared_ptr<StubLayout>& aLayout,
    const Font& aFont)
{
    auto shopItemGroup = std::make_shared<ConcreteComposite>(renderer, aLayout);

    auto itemBackgroundImage = std::make_shared<UIImage>(renderer);

    auto resourceManagerPtr = ResourceManager::getInstance();
    assert(resourceManagerPtr);
    if (!resourceManagerPtr->hasTexture("InventoryItemBackImage"))
    {
        LOG_ERROR("No texture for InventoryItemBackground");
        throw std::runtime_error("No texture for InventoryItemBackground");
    }

    itemBackgroundImage->setTexture(resourceManagerPtr->getTexture("InventoryItemBackImage"));

    Size itemSize{250, 96};
    shopItemGroup->setSize(itemSize);
    itemBackgroundImage->setSize(itemSize);
    shopItemGroup->addChild(itemBackgroundImage);

    auto shopItemIcon = std::make_shared<UIImage>(renderer);
    string iconPath = "GameData/textures/items/" + aItemCaption + ".png";
    shopItemIcon->loadTexture(iconPath);
    shopItemIcon->setSize(Size(76, 76));
    shopItemGroup->addChild(shopItemIcon);

    auto shopItemCaption = std::make_shared<UILabel>(aItemCaption, aFont, renderer);
    shopItemCaption->setPosition(shopItemGroup->getNextHorizontalPosition());
    shopItemGroup->addChild(shopItemCaption);

    auto shopItemDescription = std::make_shared<UILabel>(aItemDescription, aFont, renderer);
    Position descPos{shopItemCaption->getLocalPosition().x, shopItemGroup->getNextVerticalPosition().y};
    shopItemDescription->setPosition(descPos);
    shopItemGroup->addChild(shopItemDescription);

    view->addChild(shopItemGroup);
}
