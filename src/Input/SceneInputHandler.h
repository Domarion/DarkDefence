#pragma on
#include "../Grouping/Scene.h"
#include "InputHandler.h"

class SceneInputHandler: public InputHandler
{
public:
    SceneInputHandler();
    virtual ~SceneInputHandler();
    virtual bool onClick(SDL_Point* point) override;

    void setParentScene(Scene *value);

private:
    Scene* parentScene;
};

