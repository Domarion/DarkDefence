#include <cassert>

#include "InventoryController.h"
#include "../Grouping/FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"
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

void InventoryController::setModel(const std::shared_ptr<Inventory>& newModel)
{
	model = newModel;
}

const std::shared_ptr<Inventory>& InventoryController::getModel() const
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
    const auto& fontRef =  FontManager::getInstance()->getFontByKind("ItemFont");

    for (int i = 0; i != count; ++i)
	{
        auto itemPtr = model->getItemFromIndex(i);
        addItemView(itemPtr->getCaption(), layout, fontRef);
	}
}

void InventoryController::receiveItemFromModel(string aCaption, size_t /*itemType*/)
{
    if (aCaption.empty())
        return;

    const Font& fontRef = FontManager::getInstance()->getFontByKind("ItemFont");

    addItemView(aCaption, std::make_shared<StubLayout>(), fontRef);
}

bool InventoryController::sendItemToModel(int index)
{
    auto* item = model->getItemFromIndex(index);
    if (lastShowItemName == item->getCaption() && DescCallback)
    {
        // Remove desc item if exist;
        static auto null = std::shared_ptr<ConcreteComposite>(nullptr);
        DescCallback(null);
    }
    return model->sendItem(index);
}

void InventoryController::SetDescriptionCallBack(const InventoryController::DescriptionCallBack& aCallback)
{
    DescCallback = aCallback;
}

void InventoryController::showDescription(const std::string& aItemName)
{
    auto* itemPtr = model->getItemByName(aItemName);
    if (itemPtr == nullptr)
    {
        return;
    }

    lastShowItemName = aItemName;
    // TODO: обработка с удалением
    const std::string& description = itemPtr->getDescription();
    Size itemSize{350, 112};
    auto descriptionGroup = std::make_shared<ConcreteComposite>(renderer, std::make_shared<StubLayout>());
    descriptionGroup->setSize(itemSize);
    descriptionGroup->setPosition(Position(600, 400));
    auto itemBackgroundImage = std::make_shared<UIImage>(renderer);
    itemBackgroundImage->setTexture(ResourceManager::getInstance()->getTexture("InventoryItemBackImage"));
    descriptionGroup->addChild(itemBackgroundImage);

    auto shopItemCaption = std::make_shared<UILabel>(
        description,
        FontManager::getInstance()->getFontByKind("TextFont"),
        renderer);
    shopItemCaption->setPosition(Position(15, 15));
    descriptionGroup->addChild(shopItemCaption);

    if (DescCallback)
    {
        DescCallback(std::move(descriptionGroup));
    }
}

void InventoryController::addItemView(
    const std::string& aItemCaption,
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

    Size itemSize{350, 112};
    shopItemGroup->setSize(itemSize);
    itemBackgroundImage->setSize(itemSize);
    shopItemGroup->addChild(itemBackgroundImage);

    auto shopItemIcon = std::make_shared<UIImage>(renderer);
    string iconPath = "GameData/textures/items/" + aItemCaption + ".png";
    shopItemIcon->loadTexture(iconPath);
    shopItemIcon->setSize(Size(112, 112));
    shopItemGroup->addChild(shopItemIcon);

    auto shopItemCaption = std::make_shared<UILabel>(aItemCaption, aFont, renderer);
    shopItemCaption->setPosition(shopItemGroup->getNextHorizontalPosition());
    shopItemGroup->addChild(shopItemCaption);

    auto helpButton = std::make_shared<UIImageButton>(renderer);
    helpButton->setTexture(resourceManagerPtr->getTexture("HelpButton"));
    helpButton->setSize(Size(50, 50));
    helpButton->SetCanConsumeInput(true);
    helpButton->setPosition(
        Position(shopItemCaption->getPosition().x, shopItemGroup->getNextVerticalPosition().y));
    helpButton->ConnectMethod(std::bind(&InventoryController::showDescription, this, aItemCaption));
    shopItemGroup->addChild(helpButton);

    view->addChild(shopItemGroup);
}
