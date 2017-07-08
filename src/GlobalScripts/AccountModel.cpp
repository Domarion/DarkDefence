/*
 * AccountModel.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "AccountModel.h"
AccountModel* AccountModel::instance_ = nullptr;


AccountModel::AccountModel(int goldValue, int goldMax)
    :goldAmount(goldValue), goldLimit(goldMax)
{
	// TODO Auto-generated constructor stub

}

AccountModel* AccountModel::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new AccountModel();

	return instance_;
}

AccountModel::~AccountModel()
{
	// TODO Auto-generated destructor stub
}

const string& AccountModel::getAccountName() const
{
	return accountName;
}

void AccountModel::setAccountName(const string& aAccountName)
{
    accountName = aAccountName;
}

int AccountModel::getGoldAmount() const
{
	return goldAmount;
}

void AccountModel::setGoldAmount(int amount)
{
    if (amount < 0 || amount > goldLimit)
        return;

    goldAmount = amount;
}

bool AccountModel::PayGold(int amount)
{
	if (goldAmount >= amount)
	{
		goldAmount -= amount;
		return true;
	}

    return false;
}

void AccountModel::addGold(int amount)
{
   setGoldAmount(goldAmount + amount);
}
