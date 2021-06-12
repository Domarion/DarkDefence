#include "IHasIdentifier.h"

size_t IHasIdentifier::sId = 0;

size_t IHasIdentifier::GetId() const noexcept
{
    return mId;
}

bool IHasIdentifier::operator<(const IHasIdentifier& aLeft) const noexcept
{
    return GetId() < aLeft.GetId();
}

bool IHasIdentifier::operator==(const IHasIdentifier& aLeft) const noexcept
{
    return GetId() == aLeft.GetId();
}
