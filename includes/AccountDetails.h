#pragma once
#include <iostream>

struct AccountDetails
{
	uint32_t account_no;
	std::string name;
	std::string email;
	std::string phone;
	float cash;

	AccountDetails() : account_no(0), name{}, email{}, phone{}, cash(0.0f) {}
	AccountDetails(uint32_t _account_no,
		std::string _holder_name,
		std::string& _holder_email,
		std::string& _holder_phone,
		float _cash_amount) : account_no(_account_no), name(_holder_name), email(_holder_email), phone(_holder_phone), cash(_cash_amount) {}

	void operator=(const AccountDetails& otherSide)
	{
		account_no = otherSide.account_no;
		name = otherSide.name;
		email = otherSide.email;
		phone = otherSide.phone;
		cash = otherSide.cash;
	}

	friend std::ostream& operator<<(std::ostream& out_stream, const AccountDetails& rightSide)
	{
		out_stream << rightSide.account_no << ", " << rightSide.name << ", "
			<< rightSide.email << ", " << rightSide.phone << ", " << rightSide.cash;

		return out_stream;
	}
};