#include "Position.h"
#include <stdexcept>

Position::Position(int aX, int aY)
    : x(aX)
    , y(aY)
{
}

Position::Position(const Position& aRight)
{
    x = aRight.x;
    y = aRight.y;
}

bool Position::IsZero() const
{
    return x == 0 && y == 0;
}

Position& Position::operator=(const Position& aRight)
{
    if (this != &aRight)
    {
        x = aRight.x;
        y = aRight.y;
    }

    return *this;
}

bool Position::operator==(const Position& aRight) const
{
    return x == aRight.x && y == aRight.y;
}

bool Position::operator!=(const Position& aRight) const
{
    return !(*this == aRight);
}

Position Position::operator*(int aScalar) const
{
    return Position(x * aScalar, y * aScalar);
}

void Position::operator*=(int aScalar)
{
    x *= aScalar;
    y *= aScalar;
}

Position Position::operator*(double aScalar) const
{
    int xCoord = static_cast<int>(x * aScalar);
    int yCoord = static_cast<int>(y * aScalar);

    return Position(xCoord, yCoord);
}

void Position::operator*=(double aScalar)
{
    x = static_cast<int>(x * aScalar);
    y = static_cast<int>(y * aScalar);
}

Position Position::operator/(int aScalar) const
{
    if (aScalar == 0)
    {
        throw std::logic_error("Division by zero");
    }

    return Position(x / aScalar, y / aScalar);
}

void Position::operator/=(int aScalar)
{
    if (aScalar == 0)
    {
        throw std::logic_error("Division by zero");
    }

    x /= aScalar;
    y /= aScalar;
}

Position Position::operator+(const Position& aRight) const
{
    return Position(x + aRight.x, y + aRight.y);
}

void Position::operator+=(const Position& aRight)
{
    x += aRight.x;
    y += aRight.y;
}

Position Position::operator-(const Position& aRight) const
{
    return Position(x - aRight.x, y - aRight.y);
}

std::ostream& operator<<(std::ostream& aOutput, const Position& aRight)
{
    aOutput << '(' << aRight.x << ",\t" << aRight.y << ')';

    return aOutput;
}

std::istream& operator>>(std::istream& aInput, Position& aRight)
{
    aInput >> aRight.x >> aRight.y;

    return aInput;
}

 
