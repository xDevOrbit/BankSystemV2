#pragma once
#include "clsScreen.h"
using namespace std;

class clsDepositScreen : protected clsScreen
{
private:

public:
	static void ShowDepositScreen() {
		_DrawScreenHeader(" Deposit Screen ");
		string AccountNumber = "";
		cout << "\n Please Enter AccountNumber ..";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\n Cant Found AccountNumber ...";
			cout << "\n Please Enter AccountNumber ..";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();
		double Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadDblNumber();
		char Answer;
		cout << "\nAre you sure you want to perform this transaction? ";
		Answer = clsInputValidate::ReadChar();
		if (Answer == 'Y' || Answer == 'y') {
			Client.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client.GetAccountBalance();
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}
	


	}
};

