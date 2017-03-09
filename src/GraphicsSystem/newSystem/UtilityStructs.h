#pragma once

#include <SDL_rect.h>
#include <iostream>
struct Size
{
    Size()
        : width{0}
        , height{0}
    {
    }

    explicit Size(int aWidth, int aHeight)
        :width(aWidth), height(aHeight)
    {
    }

    bool operator==( Size const & right) const
    {
         return width == right.width && height == right.height;
    }

    bool operator!=( Size const & right) const
    {
        return !(*this == right);
    }

    bool isZero() const
    {
        return width == 0 && height == 0;
    }

    void multiplyBy(double aValue)
    {
        width *= aValue;
        height *= aValue;
    }

    int width;
    int height;

private:
     friend std::ostream& operator<<(std::ostream& output, Size const & right);
};

class Position
{
public:
   explicit Position(int posX = 0, int posY = 0)
        :x(posX), y(posY)
   {
   }
   bool operator==( Position const & right) const
   {
        return x == right.x && y == right.y;
   }

   bool operator!=( Position const & right) const
   {
       return !(*this == right);
   }


    int x, y;
private:
    friend std::ostream& operator<<(std::ostream& output, Position const & right);
};
