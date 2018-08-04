#pragma once

#include <cstddef>

class IHasIdentifier
{
public:
    size_t GetId() const noexcept;

    bool operator<(const IHasIdentifier& aLeft) const noexcept;

    bool operator==(const IHasIdentifier& aLeft) const noexcept;

private:
    size_t mId = ++sId;
    static size_t sId;
};
