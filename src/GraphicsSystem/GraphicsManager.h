#pragma once

#include "IDrawable.h"
#include <list>
using std::list;

/*
 * Назначение - отрисовка графических элементов согласно их порядку отрисовки
 * (меньше порядковый номер - раньше отрисовывается,
 * перекрывается элементами с более высоким порядковым номером)
 * Не отвечает за очищение памяти элементов
 * DEBUG:
 * Для нормального функционирования необходимы
 * два метода draw() и getDrawOrder() интерфейса IDrawable
 *
*/

class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();
    void addGraphicalItem(IDrawable* item);
    void removeGraphicalItem(IDrawable *item);
    void drawGraphicalItems();
    void clearGraphicalItems();
private:
    list<IDrawable*> uiItems;
};
