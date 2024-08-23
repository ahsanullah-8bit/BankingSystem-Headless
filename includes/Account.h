#pragma once
#include <iostream>
#include "AccountDetails.h"

class Account
{

public:
	Account(const AccountDetails& _holderDetails, class Database* db_ptr);
	void prompt();
	void updateAccount();
	void deleteAccount();
	void displayAllAccounts();

private:

	AccountDetails m_holderDetails;
	class Database* m_db_ptr;
};
