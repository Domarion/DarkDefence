#pragma once

#include <SDL_rect.h>
#include <iostream>
struct Size
{
    explicit Size(int aWidth = 0, int aHeight = 0)
        :width(aWidth), height(aHeight)
    {
    }
    int width;
    int height;
};

class Position
{
public:
   explicit Position(int posX = 0, int posY = 0)
        :x(posX), y(posY)
   {
   }
   bool operator==( Position const & right)
   {
        return x == right.x && y == right.y;
   }

   bool operator!=( Position const & right)
   {
       return !(*this == right);
   }

    int x, y;
private:
    friend bool operator==(Position const & left, Position const & right);
    friend std::ostream& operator<<(std::ostream& output, Position const & right);
};

//typedef SDL_Point Position;
