#pragma once

#include "../Grouping/Scene.h"
#include "InputHandler.h"

class SceneInputHandler : public InputHandler
{
public:


    SceneInputHandler() = default;
    virtual ~SceneInputHandler() = default;

    // InputHandler interface
    virtual bool onClick(Position aPoint) override;
    virtual bool canDrag() const override;
    virtual bool onDrag(Position aDirection) override;
    bool containsPoint(Position) const override;

    void setParentScene(std::shared_ptr<Scene> aParentScene);

private:

    std::shared_ptr<Scene> mParentScene;
};

