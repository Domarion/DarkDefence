#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{

}

GraphicsManager::~GraphicsManager()
{
    clearGraphicalItems();
}

void GraphicsManager::addGraphicalItem(IDrawable *item)//TODO:Реализовать
{

    if (item == nullptr)
        return;

    list<IDrawable*>::iterator insertPositionIterator = uiItems.begin();


    if (!uiItems.empty())
    {
        int newItemDrawOrder = item->getDrawOrder();//Ниже порядковое число - раньше отрисовывается.

        while (insertPositionIterator != uiItems.end())
        {
          int drawOrder = (*insertPositionIterator)->getDrawOrder();
          if (drawOrder >= newItemDrawOrder)
              break;

           ++insertPositionIterator;
        }
    }


    uiItems.insert(insertPositionIterator, item);// вставка в список перед позицией итератора

    /* Получение приоритета нового элемента
     * Поиск первого элемента с большим приоритетом - TODO: доработать алгоритм
     * Добавление нового перед элементом с большим приоритетом
     */
}

void GraphicsManager::removeGraphicalItem(IDrawable *item)
{
    if (item != nullptr)
        uiItems.remove(item);
}

void GraphicsManager::drawGraphicalItems()
{
    for(auto uiItem : uiItems)
       if (uiItem != nullptr)
            uiItem->draw();
}

void GraphicsManager::clearGraphicalItems()
{
    uiItems.clear();
}
