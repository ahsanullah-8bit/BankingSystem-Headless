#include "Transaction.h"
#include "BS_Exceptions.h"
#include "Database.h"

Transaction::Transaction(const AccountDetails& holderDet, Database* dbase_ptr) : m_holderDetails(holderDet), m_db_ptr(dbase_ptr) {}

void Transaction::prompt()
{
	char choice;
	std::cout << "____________ Transaction ______________\n\n";

	std::cout << "Your balance : " << m_holderDetails.cash << "\n\n";
	std::cout << "1. Deposite\n2. Withdraw\n3. Transfer\n4. Back\nYour choice : ";
	std::cin >> choice;
	std::cin.ignore();

	if (choice == '1')
		deposite();
	else if (choice == '2')
		withdraw();
	else if (choice == '3')
		transfer();
}

void Transaction::deposite()
{
	std::cout << "____________ Deposite ______________\n\n";

	try {
		float amount;
		std::cout << "Enter amount : ";
		std::cin >> amount;
		std::cin.ignore();

		if (amount < 500.0f || amount >= 100000)
			throw InvalidAmount();

		m_db_ptr->transactionDeposite(m_holderDetails, amount);
	}
	catch (InvalidAmount& ex)
	{
		std::cout << "Deposite Error : " << ex.what() << std::endl;
		return;
	}
}

void Transaction::withdraw()
{
	std::cout << "____________ Withdraw ______________\n\n";

	try {
		float amount;
		std::cout << "Enter amount : ";
		std::cin >> amount;
		std::cin.ignore();

		if (amount < 500.0f || amount >= FLT_MAX)
			throw InvalidAmount();

		m_db_ptr->transactionWithdraw(m_holderDetails, amount);
	}
	catch (InvalidAmount& ex)
	{
		std::cout << "Withdraw Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}

void Transaction::transfer()
{
	std::cout << "____________ Transfer ______________\n\n";

	try {
		AccountDetails to_account;
		float amount;
		std::cout << "Enter reciever account number : ";
		std::cin >> to_account.account_no;
		std::cin.ignore();
		std::cout << "Enter amount : ";
		std::cin >> amount;
		std::cin.ignore();

		if (amount < 500.0f || amount >= FLT_MAX)
			throw InvalidAmount();

		m_db_ptr->transactionTransfer(m_holderDetails, to_account, amount);
	}
	catch (InvalidAmount& ex)
	{
		std::cout << "Error : " << ex.what() << " at line " << __LINE__ << ", file : " << __FILE__ << std::endl;
		return;
	}
}