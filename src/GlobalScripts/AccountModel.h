/*
 * AccountModel.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <string>
using std::string;

class AccountModel
{
public:
	static AccountModel* const getInstance();
	const string& getAccountName() const;
	void setAccountName(const string& accountName);
	int getGoldAmount() const;
	void setGoldAmount(int goldAmount);
	bool PayGold(int amount);
    void addGold(int amount);
private:
	AccountModel();
	~AccountModel();
	string accountName;
	int goldAmount;
	static AccountModel* instance_;
};

