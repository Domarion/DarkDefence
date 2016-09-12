#include "EnemyInfo.h"

EnemyInfo::EnemyInfo()
    :tag(), reaction(EReaction::Attack), priority(0)
{

}

EnemyInfo::EnemyInfo(const string &aTag, EReaction aReaction, int aPriority)
    :tag(aTag), reaction(aReaction), priority(aPriority)
{

}

string EnemyInfo::getTag() const
{
    return tag;
}

void EnemyInfo::setTag(const string &value)
{
    tag = value;
}

EReaction EnemyInfo::getReaction() const
{
    return reaction;
}

void EnemyInfo::setReaction(const EReaction &value)
{
    reaction = value;
}

int EnemyInfo::getPriority() const
{
    return priority;
}

void EnemyInfo::setPriority(int value)
{
    priority = value;
}
