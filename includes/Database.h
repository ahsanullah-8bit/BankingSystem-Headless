#pragma once
#include <mysql/jdbc.h>
#include "AccountDetails.h"

// ________________________________________________________________
class Database
{

public:
	Database();
	void connect(const std::string& host = "localhost", const std::string& username = "root", const std::string& password = "root");
	bool addAccount(const AccountDetails& account_det);
	bool checkAccount(AccountDetails& account_det);
	void updateAccount(const AccountDetails& new_acc_data, uint32_t older_acc_no);
	void removeAccount(uint32_t account_no);
	void getAccountData(AccountDetails& holderDetails);
	std::shared_ptr<sql::ResultSet> getAllAccountsData();

	// Transaction
	void transactionDeposite(const AccountDetails& to_account, float amount);
	void transactionWithdraw(const AccountDetails& from_account, float amount);
	void transactionTransfer(const AccountDetails& from_account, const AccountDetails& to_Account, float amount);
private:
	sql::Driver* m_driver;
	std::unique_ptr<sql::Connection> m_connection;
	std::unique_ptr<sql::Statement> m_statement;
	std::shared_ptr<sql::ResultSet>	m_resultset;
};