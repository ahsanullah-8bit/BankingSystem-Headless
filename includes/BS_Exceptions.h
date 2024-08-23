#pragma once
#include <string>

// _______________________________________________________________
class BankingSystem_Exceptions
{
public:
	virtual std::string what() = 0;
};

// Invalid Amount
class InvalidAmount : BankingSystem_Exceptions
{
public:
	std::string what() override
	{
		return "Invalid amount, it should be b/w (500, 100,000)";
	}
};

// Invalid Account Number
class InvalidAccountNumber : BankingSystem_Exceptions
{
public:
	std::string what() override
	{
		return "Invalid Account number";
	}
};
