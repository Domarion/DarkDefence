#include "UtilityStructs.h"

std::ostream& operator<<(std::ostream &output, const Position &right)
{
    output << '(' << right.x << ",\t" << right.y << ')';
    return output;
}

std::ostream& operator<<(std::ostream &output, const Size &right)
{
    output << '(' << right.width << ",\t" << right.height << ')';
    return output;
}
