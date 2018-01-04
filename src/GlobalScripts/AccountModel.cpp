#include "AccountModel.h"

AccountModel* AccountModel::instance_ = nullptr;

AccountModel::AccountModel(int aGoldValue, int aGoldMax)
    : mGoldAmount(aGoldValue)
    , mGoldAmountLimit(aGoldMax)
{
}

AccountModel* AccountModel::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new AccountModel();

	return instance_;
}

const std::string& AccountModel::getAccountName() const
{
	return mAccountName;
}

void AccountModel::setAccountName(const std::string& aAccountName)
{
    mAccountName = aAccountName;
}

int AccountModel::getGoldAmount() const
{
	return mGoldAmount;
}

void AccountModel::setGoldAmount(int aAmount)
{
    if (aAmount < 0 || aAmount > mGoldAmountLimit)
        return;

    mGoldAmount = aAmount;
}

bool AccountModel::PayGold(int aAmount)
{
    if (mGoldAmount >= aAmount)
	{
        mGoldAmount -= aAmount;
		return true;
	}

    return false;
}

void AccountModel::addGold(int aAmount)
{
   setGoldAmount(mGoldAmount + aAmount);
}
