#include <iostream>
#include "jdbc/cppconn/resultset.h"
#include "AccountDetails.h"
#include "Database.h"
#include "Account.h"
#include "Transaction.h"

Account::Account(const AccountDetails& _holderDetails, Database* dbase_ptr) : m_holderDetails(_holderDetails), m_db_ptr(dbase_ptr) {}

void Account::prompt()
{

	char choice;
	do {
		std::cout << "\n\n____________ Account ______________\n\n" << std::endl;
		std::cout << "Your account: " << m_holderDetails << std::endl;
		std::cout << "1. Transaction\n2. Update Account\n3. Delete Account\n4. All Accounts\n5. Back\nYour choice : ";
		std::cin >> choice;
		std::cin.ignore();

		if (choice == '1')
		{
			Transaction transction(m_holderDetails, m_db_ptr);
			transction.prompt();
		}
		else if (choice == '2')
			updateAccount();
		else if (choice == '3')
		{
			deleteAccount();
			return; // Pretending account removed
		}
		else if (choice == '4')
			displayAllAccounts();

		m_db_ptr->getAccountData(m_holderDetails); // Update data
	} while (choice != '5');
}

void Account::updateAccount()
{
	std::cout << "\n\n____________ Update Account ______________\n\n" << std::endl;
	AccountDetails new_data;

	//uint32_t account_no;
	/*std::cout << "Enter the Account No : ";
	std::cin >> new_data.account_no;
	std::cin.ignore();*/

	std::cout << "Enter the new name : ";
	std::getline(std::cin, new_data.name);

	std::cout << "Enter the new email : ";
	std::getline(std::cin, new_data.email);

	std::cout << "Enter the new phone : ";
	std::getline(std::cin, new_data.phone);

	m_db_ptr->updateAccount(new_data, m_holderDetails.account_no);
}

void Account::deleteAccount()
{
	m_db_ptr->removeAccount(this->m_holderDetails.account_no);
}

void Account::displayAllAccounts()
{
	std::cout << "\n\n____________ All Accounts ______________\n\n" << std::endl;
	try
	{
		std::shared_ptr<sql::ResultSet> resultset = m_db_ptr->getAllAccountsData();

		if (!resultset) return;

		while (resultset->next())
		{
			std::cout << resultset->getInt("account_no") << ", "
				<< resultset->getString("name") << ", "
				<< resultset->getString("phone") << ", "
				<< resultset->getString("email") << ", "
				<< resultset->getDouble("cash_amount") << std::endl;
		}
	}
	catch (sql::SQLException& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}
