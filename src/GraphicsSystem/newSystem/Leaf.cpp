#include "Leaf.h"
#include <exception>

/*
 * TODO:: Задавать флаг положения (aligment) при добавлении дочернего элемента в Composite
 * TODO:: Расчёт маштабированного размера дочерних элементов внутри родительского элемента.
 * TODO:: Перенос расчёта начальной локальной позиции в родительский элемент.
 * Всё это для применения масштабирования в зависимости от разрешения
 */
Leaf::Leaf(std::shared_ptr<RenderingSystem>& aRenderingContext)
    :IComposite()
    , renderer(aRenderingContext)
{

}

void Leaf::addChild(const shared_ptr<IComposite> &/*child*/)
{

    throw std::logic_error("Error: add child to leaf");
}

void Leaf::removeChild(const shared_ptr<IComposite> &/*child*/)
{
    throw std::logic_error("Error: remove child from leaf");

}

weak_ptr<IComposite> Leaf::getParent() const
{
    return parent;
}

Position Leaf::getPosition() const
{
    Position globalPosition = localPosition;
    if (hasParent())
    {
        shared_ptr<IComposite>  parentPtr = getParent().lock();
        Position parentPosition = parentPtr->getPosition();
        globalPosition.x += parentPosition.x;
        globalPosition.y += parentPosition.y;
    }
    return globalPosition;
}

void Leaf::setPosition(Position pos)
{
    if (hasParent() && (pos.x < 0 || pos.y < 0))
            throw std::logic_error("Error: relative to parent coord cannot be less than 0");
    localPosition = pos;
}

void Leaf::setParent(weak_ptr<IComposite> aParent)
{
    parent = aParent;
}
bool Leaf::hasParent() const
{
    return !(getParent().expired());
}

Position Leaf::getLocalPosition() const//TODO:: Перенести в базовый интерфейс IComposite
{
    return localPosition;
}

void Leaf::setLocalPosition(Position aPosition)
{
    localPosition = aPosition;
}

void Leaf::setScalingFactor(double aScaleFactor)
{
    if (mScaleFactor == aScaleFactor)
        return;

    mScaleFactor = aScaleFactor;
    mScaledSize = getSize();
    mScaledSize.multiplyBy(mScaleFactor);
    this->setSize(mScaledSize);
}

double Leaf::getScalingFactor() const
{
    return mScaleFactor;
}
