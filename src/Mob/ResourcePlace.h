#pragma once
#include "../Grouping/SceneObject.h"
#include "../Input/InputHandler.h"
#include "../Enums.h"

class ResourcePlace:
        public SceneObject
        , public InputHandler
        , public std::enable_shared_from_this<ResourcePlace>
{
public:
    ResourcePlace();
    ResourcePlace(int aLimit, Enums::ResourceTypes aResourceType);
    virtual ~ResourcePlace();
    void setLimit(int amount);
    Enums::ResourceTypes getResourceType() const;
    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;

    // SceneObject interface
public:

    virtual bool update(double timestep) override;
    virtual void finalize() override;
private:
    int limit;
    Enums::ResourceTypes resourceType;

};

