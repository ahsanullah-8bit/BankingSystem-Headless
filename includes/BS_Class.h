#pragma once
#include "Database.h"

class BankingSystemClass
{
	Database m_database;
public:
	BankingSystemClass();
	BankingSystemClass(const Database& database);
	void prompt();
private:
	void signIn();
	void signUp();
};
