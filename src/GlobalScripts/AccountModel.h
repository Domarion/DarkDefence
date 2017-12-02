/*
 * AccountModel.h
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <string>
using std::string;

class AccountModel final
{
public:
    static AccountModel* getInstance();
	const string& getAccountName() const;
    void setAccountName(const string& aAccountName);
	int getGoldAmount() const;
    void setGoldAmount(int amount);
	bool PayGold(int amount);
    void addGold(int amount);
private:
    AccountModel(int goldValue = 300, int goldMax = 5000);
    ~AccountModel() = default;
	string accountName;
    int goldAmount, goldLimit;
	static AccountModel* instance_;
};

