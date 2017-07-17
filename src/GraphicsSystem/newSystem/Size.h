#pragma once

#include <iostream>

struct Size final
{
private:

    friend std::ostream& operator<<(std::ostream& aOutput, const Size& aRight);
    friend std::istream& operator>>(std::istream& aInput, Size& aRight);

public:

    Size(int aWidth = 0, int aHeight = 0);
    Size(const Size& aRight);

    bool IsZero() const;

    Size& operator= (const Size& aRight);

    bool operator== (Size const& aRight) const;

    bool operator!= (Size const& aRight) const;

    Size operator* (int aScalar) const;
    void operator*= (int aScalar);

    Size operator* (double aScalar) const;
    void operator*= (double aScalar);


    Size operator/ (int aScalar) const;
    void operator/= (int aScalar);


    Size operator+ (const Size& aRight) const;
    void operator+= (const Size& aRight);

    int width;
    int height;
};

extern std::ostream& operator<<(std::ostream& aOutput, const Size& aRight);
extern std::istream& operator>>(std::istream& aInput, Size& aRight); 
