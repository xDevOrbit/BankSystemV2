#pragma once
#include "clsScreen.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:

public:
	static void ShowWithdrawScreen() {
		_DrawScreenHeader(" Withdraw Screen ");
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
		cout << "\nPlease enter Withdraw amount? ";
		Amount = clsInputValidate::ReadDblNumber();
		char Answer;
		cout << "\nAre you sure you want to perform this transaction? ";
		Answer = clsInputValidate::ReadChar();
		if (Answer == 'Y' || Answer == 'y') {
			if (Client.Withdraw(Amount)) {
				cout << "\nAmount Withdraw Successfully.\n";
				cout << "\nNew Balance Is: " << Client.GetAccountBalance();
			}
			else {
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client.GetAccountBalance();
			}

		}
		else {
			cout << "\nOperation was cancelled.\n";
		}



	}
};


