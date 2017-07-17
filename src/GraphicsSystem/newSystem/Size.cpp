#include "Size.h"
#include <exception>

Size::Size(int aWidth, int aHeight)
    : width(aWidth)
    , height(aHeight)
{
}

Size::Size(const Size& aRight)
{
    width = aRight.width;
    height = aRight.height;
}

bool Size::IsZero() const
{
    return width == 0 && height == 0;
}

Size& Size::operator=(const Size& aRight)
{
    if (this != &aRight)
    {
        width = aRight.width;
        height = aRight.height;
    }

    return *this;
}

bool Size::operator==(const Size& aRight) const
{
    return width == aRight.width && height == aRight.height;
}

bool Size::operator!=(const Size& aRight) const
{
    return !(*this == aRight);
}

Size Size::operator*(int aScalar) const
{
    return Size(width * aScalar, height * aScalar);
}

void Size::operator*=(int aScalar)
{
    width *= aScalar;
    height *= aScalar;
}

Size Size::operator*(double aScalar) const
{
    int w = static_cast<int>(width * aScalar);
    int h = static_cast<int>(height * aScalar);

    return Size(w, h);
}

void Size::operator*=(double aScalar)
{
    width = static_cast<int>(width * aScalar);
    height = static_cast<int>(height * aScalar);
}

Size Size::operator/(int aScalar) const
{
    if (aScalar == 0)
    {
        throw std::logic_error("Division bheight zero");
    }

    return Size(width / aScalar, height / aScalar);
}

void Size::operator/=(int aScalar)
{
    if (aScalar == 0)
    {
        throw std::logic_error("Division bheight zero");
    }

    width /= aScalar;
    height /= aScalar;
}

Size Size::operator+(const Size& aRight) const
{
    return Size(width + aRight.width, height + aRight.height);
}

void Size::operator+=(const Size& aRight)
{
    width += aRight.width;
    height += aRight.height;
}

std::ostream& operator<<(std::ostream& aOutput, const Size& aRight)
{
    aOutput << '(' << aRight.width << ",\t" << aRight.height << ')';

    return aOutput;
}

std::istream& operator>>(std::istream& aInput, Size& aRight)
{
    aInput >> aRight.width >> aRight.height;

    return aInput;
}
 
