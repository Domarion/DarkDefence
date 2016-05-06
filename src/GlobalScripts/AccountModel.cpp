/*
 * AccountModel.cpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "AccountModel.h"
AccountModel* AccountModel::instance_ = nullptr;


AccountModel::AccountModel()
    :goldAmount(0)
{
	// TODO Auto-generated constructor stub

}

AccountModel* const AccountModel::getInstance()
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

void AccountModel::setAccountName(const string& accountName)
{
	this->accountName = accountName;
}

int AccountModel::getGoldAmount() const
{
	return goldAmount;
}

void AccountModel::setGoldAmount(int goldAmount)
{
	this->goldAmount = goldAmount;
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
    goldAmount += amount;
}
