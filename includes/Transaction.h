#pragma once
#include "AccountDetails.h"

class Transaction
{
public:
	Transaction(const AccountDetails& _account_pp, class Database* dbase_ptr);
	void prompt();
	void deposite();
	void withdraw();
	void transfer();

private:
	//Database database;
	AccountDetails m_holderDetails;
	class Database* m_db_ptr;
};