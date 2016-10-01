#include "UtilityStructs.h"
bool operator==(Position const & left, Position const & right)
{
     return left.x == right.x && left.y == right.y; ;
}

std::ostream& operator<<(std::ostream &output, const Position &right)
{
    output << '(' << right.x << ",\t" << right.y << ')';
    return output;
}
