#pragma once

#include <iostream>

struct Position final
{
private:

    friend std::ostream& operator<<(std::ostream& aOutput, const Position& aRight);
    friend std::istream& operator>>(std::istream& aInput, Position& aRight);

public:

    Position(int aX = 0, int aY = 0);
    Position(const Position& aRight);

    bool IsZero() const;
    int ComputeDistanceSqr(Position aRight) const;

    Position& operator= (const Position& aRight);

    bool operator== (Position const& aRight) const;

    bool operator!= (Position const& aRight) const;

    Position operator* (int aScalar) const;
    void operator*= (int aScalar);

    Position operator* (double aScalar) const;
    void operator*= (double aScalar);


    Position operator/ (int aScalar) const;
    void operator/= (int aScalar);

    Position operator+ (const Position& aRight) const;
    void operator+= (const Position& aRight);

    Position operator- (const Position& aRight) const;
    void operator-= (const Position& aRight);


    int x = 0;
    int y = 0;
};
 
