#pragma once
#include <SDL.h>
#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

#include "Font.h"
#include "UtilityStructs.h"

class Texture2D final
{
public:
    Texture2D();
    virtual ~Texture2D() = default;
    void setTexture(shared_ptr<SDL_Texture> texture);
    void setTextureFromText(const string& ltext, Font lfont);

    shared_ptr<SDL_Texture> getTexture() const;
    void loadTexture(const string& filename);
    void drawAtPosition(Position pos);
    Size getSize() const;
    void setSize(Size size);
    void scaleToTexture();
private:
    shared_ptr<SDL_Texture> texturePtr;
    Size textureSize;
};

