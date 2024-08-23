#include <iostream>
#include "BS_Class.h"
#include "Account.h"


BankingSystemClass::BankingSystemClass()
{
	m_database.connect("localhost", "root", "root");
}

BankingSystemClass::BankingSystemClass(const Database& database)
	: m_database(database)
{}

void BankingSystemClass::prompt()
{
	std::cout << "____________ Bank ______________" << std::endl;

	char choice;
	do {
		std::cout << "1. Sign in\n2. Sign up\n3. Back\nYour choice : ";
		std::cin >> choice;
		std::cin.ignore();

		if (choice == '1')
			signIn();
		else if (choice == '2')
			signUp();

	} while (choice != '3');
}

void BankingSystemClass::signIn()
{

	std::cout << "\n\n____________ Sign In ______________\n\n" << std::endl;
	AccountDetails _account;

	/*std::cout << "Enter account no : ";
	std::cin >> _account.account_no;
	std::cin.ignore();*/

	std::cout << "Enter the name : ";
	std::getline(std::cin, _account.name);

	std::cout << "Enter the email : ";
	std::getline(std::cin, _account.email);

	if (!m_database.checkAccount(_account)) // Check account, feed the rest data if exists
	{
		std::cout << "\nNo such account!\n" << std::endl;
		return;
	}

	Account account(_account, &m_database);
	account.prompt();
}

void BankingSystemClass::signUp()
{
	std::cout << "\n\n____________ Sign Up ______________\n\n" << std::endl;
	AccountDetails new_account;

	std::cout << "Enter the name : ";
	std::getline(std::cin, new_account.name);

	std::cout << "Enter the email : ";
	std::getline(std::cin, new_account.email);

	std::cout << "Enter the phone : ";
	std::getline(std::cin, new_account.phone);

	std::cout << "Enter first Deposite Amount : ";
	std::cin >> new_account.cash;
	std::cin.ignore();

	m_database.addAccount(new_account);

	if (!m_database.checkAccount(new_account)) // Check if added and get the rest data
	{
		std::cout << "\nAccount not added successfully!\n" << std::endl;
		return;
	}

	std::cout << "\nAccount added successfully!\n" << std::endl;
	Account account(new_account, &m_database);
	account.prompt();
}
