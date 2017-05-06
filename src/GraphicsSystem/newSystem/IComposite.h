#pragma once

#include "UtilityStructs.h"
#include <memory>

using std::shared_ptr;
using std::weak_ptr;

class IComposite
{
public:
    virtual ~IComposite() = default;
    virtual void addChild(const shared_ptr<IComposite>& child) = 0;
    virtual void removeChild(const shared_ptr<IComposite>& child) = 0;
    virtual void draw() const = 0;
    virtual weak_ptr<IComposite> getParent() const = 0;
    virtual void setParent(weak_ptr<IComposite> aParent) = 0;
    virtual Position getPosition() const = 0;
    virtual Position getLocalPosition() const = 0;
    virtual void setLocalPosition(Position aPosition) = 0;
    virtual void setPosition(Position pos) = 0;
    virtual Size getSize() const = 0;
    virtual void setSize(Size size) = 0;
    virtual bool hasParent() const = 0;
    virtual void clearChildren(){}
    virtual void setScalingFactor(double aScaleFactor) = 0;
    virtual double getScalingFactor() const  = 0;
};
