#pragma once

#include <string>

class AccountModel final
{
public:
    static AccountModel* getInstance();

    const std::string& getAccountName() const;
    void setAccountName(const std::string& aAccountName);

	int getGoldAmount() const;
    void setGoldAmount(int aAmount);

    bool PayGold(int aAmount);
    void addGold(int aAmount);

private:
    AccountModel(int aGoldValue = 300, int aGoldMax = 5000);
    ~AccountModel() = default;

    std::string mAccountName;
    int mGoldAmount = 0, mGoldAmountLimit = 0;
	static AccountModel* instance_;
};

