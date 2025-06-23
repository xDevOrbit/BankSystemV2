#pragma once
#include "clsScreen.h"
class clsTansferScreen : protected clsScreen
{
private:
	static void _PrintCard(clsBankClient client) {
		cout << "\n CLient Card : "
			<< "\n--------------------------"
			<< "\nFull Name : " + client.FullName()
			<< "\nAcc. Number : " + client.GetAccountNumber()
			<< "\nBalance : " + to_string(client.GetAccountBalance())
			<< "\n---------------------------";
	}
public:
	static void ShowTansferScreen() {
		_DrawScreenHeader("Tansfer Screen");
		string TranFrom, TranTo;
		cout << "\n Please Enter Account Number To Transfer From : ";
		TranFrom = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(TranFrom)) {
			cout << "\n Cant Found Account Number ..";
			cout << "\n Please Enter Account Number To Transfer From : ";
			TranFrom = clsInputValidate::ReadString();
		}
		clsBankClient ClientFrom = clsBankClient::Find(TranFrom);
		_PrintCard(ClientFrom);

		cout << "\n Please Enter Account Number To Transfer To : ";
		TranTo = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(TranTo)) {
			cout << "\n Cant Found Account Number ..";
			cout << "\n Please Enter Account Number To Transfer To : ";
			TranTo = clsInputValidate::ReadString();
		}
		clsBankClient ClientTo = clsBankClient::Find(TranTo);
		_PrintCard(ClientTo);
		double Amount = 0;
		cout << "\n Enter Tansfer Amount : ";
		Amount = clsInputValidate::ReadDblNumber();
		while (Amount > ClientFrom.GetAccountBalance()) {
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ?";
			Amount = clsInputValidate::ReadDblNumber();
		}
		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation? y/n?";
		Answer = clsInputValidate::ReadChar();
		if (Answer == 'y' || Answer == 'Y') {
			
			if (ClientFrom.Transfer(ClientTo, Amount)) {
				cout << "\n Transfer done successfully";
				_PrintCard(ClientFrom);
				_PrintCard(ClientTo);
			}
			else {
				cout << "\n Error";
			}
		}


	}

};

