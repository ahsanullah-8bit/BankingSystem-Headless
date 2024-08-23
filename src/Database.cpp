#include <sstream>
#include "Database.h"


#define MIN_ACCNUM_DIGITS 1
#define MAX_ACCNUM_DIGITS UINT32_MAX

Database::Database() : m_driver(nullptr), m_connection(nullptr), m_statement(nullptr), m_resultset(nullptr) {	}

void Database::connect(const std::string& host, const std::string& username, const std::string& password)
{
	try
	{
		// Driver
		m_driver = sql::mysql::get_driver_instance();

		// Connection
		m_connection = std::unique_ptr<sql::Connection>(m_driver->connect(host, username, password));

		// Statement
		m_statement = std::unique_ptr<sql::Statement>(m_connection->createStatement());

		// Schema Creation
		m_statement->execute("CREATE DATABASE IF NOT EXISTS bankingsystem_db");
		m_statement->execute("USE bankingsystem_db");

		// Accounts Table
		m_statement->execute(R"(CREATE TABLE IF NOT EXISTS accounts(
								account_no INT NULL UNIQUE AUTO_INCREMENT,
								name VARCHAR(45) UNIQUE NOT NULL,
								phone VARCHAR(45) NOT NULL UNIQUE,
								email VARCHAR(45) UNIQUE NOT NULL,
								cash_amount DOUBLE NOT NULL) AUTO_INCREMENT = 500000)");

		//// Transaction Table
		//m_statement->execute(R"(CREATE TABLE IF NOT EXISTS transactions(
		//						transaction_id INT NULL UNIQUE AUTO_INCREMENT, 
		//						from_acc VARCHAR(45) NULL DEFAULT 'self',
		//						to_acc VARCHAR(45) NULL DEFAULT 'self',
		//						cash_amount DOUBLE NOT NULL) AUTO_INCREMENT = 100)");
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

bool Database::addAccount(const AccountDetails& account_det)
{
	try
	{
		std::stringstream all_args;
		all_args << "'" << account_det.name << "','" << account_det.phone << "','"
			<< account_det.email << "'," << account_det.cash;

		m_statement->execute("INSERT INTO accounts VALUES(NULL," + all_args.str() + ")");
		return true;
	}
	catch (sql::SQLException& ex)
	{
		std::cout << ex.what() << std::endl;
		return false;
	}
}

bool Database::checkAccount(AccountDetails& account_det)
{
	std::stringstream query_args;
	query_args << "name = '" << account_det.name << "' AND email REGEXP '^" << account_det.email << "'";
	m_resultset = std::shared_ptr<sql::ResultSet>(m_statement->executeQuery("SELECT * FROM accounts WHERE " + query_args.str()));

	if (!m_resultset->next()) return false;

	// Set the rest details
	account_det.account_no = std::stoi(m_resultset->getString("account_no"));

	if (account_det.phone.empty())
		account_det.phone = m_resultset->getString("phone");

	account_det.cash = (float)m_resultset->getDouble("cash_amount");

	return true;
}

void Database::updateAccount(const AccountDetails& new_acc_data, uint32_t older_acc_no)
{
	try
	{
		if (older_acc_no < MIN_ACCNUM_DIGITS) return;

		std::string all_args = "";
		if (!new_acc_data.name.empty())	// New Name entered
			all_args += ("name = '" + new_acc_data.name + "'");

		if (!new_acc_data.phone.empty()) // New Phone entered
		{
			// In case, first one wasn't entered
			// don't add comma
			all_args += (!all_args.empty() ? "," : "");
			all_args += "phone = '" + new_acc_data.phone + "'";
		}

		if (!new_acc_data.email.empty()) // New email entered
		{
			all_args += (!all_args.empty() ? "," : "");
			all_args += "email = '" + new_acc_data.email + "'";
		}

		// No new data entered
		if (all_args.empty()) return;

		m_statement->execute("UPDATE accounts SET " + all_args + " WHERE account_no = " + std::to_string(older_acc_no));
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

void Database::removeAccount(uint32_t account_no)
{
	try
	{
		m_statement->execute("DELETE FROM accounts WHERE account_no = " + std::to_string(account_no));
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

void Database::getAccountData(AccountDetails& holderDetails)
{
	try
	{
		m_resultset = std::shared_ptr<sql::ResultSet>(m_statement->executeQuery("SELECT * FROM accounts WHERE account_no = " + std::to_string(holderDetails.account_no)));

		if (!m_resultset->next())
		{
			std::cout << "No account found while getting data!" << std::endl;
			return;
		}

		holderDetails.name = m_resultset->getString("name");
		holderDetails.email = m_resultset->getString("email");
		holderDetails.phone = m_resultset->getString("phone");
		holderDetails.cash = (float)m_resultset->getDouble("cash_amount");
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

std::shared_ptr<sql::ResultSet> Database::getAllAccountsData()
{
	try
	{
		return std::shared_ptr<sql::ResultSet>(m_statement->executeQuery("SELECT * FROM accounts"));
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return nullptr;
	}
}

void Database::transactionDeposite(const AccountDetails& to_account, float amount)
{
	try
	{
		// Add the money

		std::string query = "UPDATE accounts SET cash_amount = cash_amount + " + std::to_string(amount) + " WHERE account_no = " + std::to_string(to_account.account_no);
		m_statement->execute(query);

		//// Update history
		//all_args.clear();
		//all_args << "'" << to_account.account_no << "'," << std::to_string(amount);
		//m_statement->execute("INSERT INTO transactions VALUES(NULL, NULL, " + all_args.str() + ")");
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
	catch (...)
	{
		std::cout << "Error : Unhandeled " << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

void Database::transactionWithdraw(const AccountDetails& from_account, float amount)
{
	try
	{
		// Remove the money
		std::string query = "UPDATE accounts SET cash_amount = cash_amount - " + std::to_string(amount) + " WHERE account_no = " + std::to_string(from_account.account_no);
		m_statement->execute(query);

		// Update history
		//all_args.clear();
		//all_args << "'" << from_account.account_no << "',NULL," << std::to_string(amount);
		//m_statement->execute("INSERT INTO transactions VALUES(NULL, " + all_args.str() + ")");
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

void Database::transactionTransfer(const AccountDetails& from_account, const AccountDetails& to_account, float amount)
{
	try
	{
		// Remove the money
		std::string query_remove = "UPDATE accounts SET cash_amount = cash_amount - " + std::to_string(amount) + " WHERE account_no = " + std::to_string(from_account.account_no);
		m_statement->execute(query_remove);

		// Add the money
		std::string query_add = "UPDATE accounts SET cash_amount = cash_amount + " + std::to_string(amount) + " WHERE account_no = " + std::to_string(to_account.account_no);
		m_statement->execute(query_add);

		/*all_args.clear();*/

		//// Update history
		//all_args << "'" << from_account.account_no << "','" << to_account.account_no << "'," << std::to_string(amount);
		//m_statement->execute("INSERT INTO transactions VALUES(NULL, " + all_args.str() + ")");
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}