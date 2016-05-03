#pragma once
#include <functional>
#include "../CTexture.h"
#include "../../Input/InputHandler.h"
#include <string>
using std::string;
class ImageButton: public CTexture, public InputHandler
{
public:
    ImageButton();
    virtual ~ImageButton();
    virtual bool onClick(SDL_Point* point) override;

    virtual void ConnectMethod(std::function<void(string)> method);

protected:
    std::function<void(string)> connectedMethod;

};

