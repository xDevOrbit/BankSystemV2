#pragma once
// BankSystemV2.cpp : Abdullah -> DevOrBit.dev

#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <string>
#include "clsScreen.h"
#include <vector>
#include <fstream>
#include "global.h"

using namespace std;
class clsBankClient : public clsPerson
{
private:
	enum enMode{EmpatyMode=0,UpdateMode=1,AddNewMode=3};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool MarkForDeleted = false;
	struct stTransferdata;
	static clsBankClient _ConvetLineToClientObject(string line, string Sepretor = "#//#") {
		vector<string>vStrings;
		vStrings = clsString::Split(line, Sepretor);
		return clsBankClient(enMode::UpdateMode, vStrings[0], vStrings[1], vStrings[2], vStrings[3], vStrings[4], vStrings[5], stod(vStrings[6]));
	}
	static stTransferdata _ConvetLineToDataTransferLogs(string line, string Sepretor = "#//#") {
		vector<string>vStrings;
		stTransferdata logs;
		vStrings = clsString::Split(line, Sepretor);
		logs.DateTran = vStrings[0];
		logs.ClientFrom = vStrings[1];
		logs.ClientTo = vStrings[2];
		logs.Amount = stoi(vStrings[3]);
		logs.BalanceFrom = stoi(vStrings[4]);
		logs.BalanceTo = stoi(vStrings[5]);
		logs.User = vStrings[6];
		return logs;

	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmpatyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsFromFile() {
		vector<clsBankClient>vClients;
		fstream MyFile;
		string line;
		MyFile.open("Clients.txt", ios::in);
		while (getline(MyFile, line)) {
			clsBankClient client = _ConvetLineToClientObject(line);
			vClients.push_back(client);
		}
		MyFile.close();
		return vClients;
	}
	static vector<stTransferdata> _LoadTransferLogsFromFile() {
		vector<stTransferdata>vLogs;
		fstream MyFile;
		string line;
		MyFile.open("TransferLogs.txt", ios::in);
		while (getline(MyFile, line)) {
			stTransferdata log = _ConvetLineToDataTransferLogs(line);
			vLogs.push_back(log);
		}
		MyFile.close();
		return vLogs;
	}

	static string _ConverClientObjectToLine( clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.GetFirstName() + Seperator;
		stClientRecord += Client.GetLastName() + Seperator;
		stClientRecord += Client.GetEmail() + Seperator;
		stClientRecord += Client.GetPhone() + Seperator;
		stClientRecord += Client.GetAccountNumber() + Seperator;
		stClientRecord += Client.GetPinCode() + Seperator;
		stClientRecord += to_string(Client.GetAccountBalance());

		return stClientRecord;

	}
	 string _ConverTransferLogsToLine(clsBankClient Client,double Amount, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += clsDate::GetSystemDateTimeString() + Seperator;
		stClientRecord += this->GetAccountNumber() + Seperator;
		stClientRecord += Client.GetAccountNumber() + Seperator;
		stClientRecord += to_string(Amount) + Seperator;
		stClientRecord += to_string(this->GetAccountBalance()) + Seperator;
		stClientRecord += to_string(Client.GetAccountBalance()) + Seperator;
		stClientRecord += CurrentUser.GetUserName();
		return stClientRecord;

	}
	static void _SaveDataToFile(vector<clsBankClient> vClients) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient &C : vClients)
			{
				if (C.MarkForDeleted == false) {
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}
	}
	void _Update() {
		vector<clsBankClient>_vClients;
		_vClients = _LoadClientsFromFile();
		for (clsBankClient& c : _vClients) {
			if (c.GetAccountNumber() == GetAccountNumber()) {
				c = *this;
				break;
			}
		}
		_SaveDataToFile(_vClients);

	}
	void _AddDataLineToFile(string line) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app | ios::out);
		if (MyFile.is_open()) {
			MyFile << line << endl;
		}

		MyFile.close();

	}
	void _AddDataTransferLogsToFile(string line) {
		fstream MyFile;
		MyFile.open("TransferLogs.txt", ios::app | ios::out);
		if (MyFile.is_open()) {
			MyFile << line << endl;
		}

		MyFile.close();

	}
	void _AddNewClient() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));

	}
public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;	
	}
	struct stTransferdata {
		string DateTran, ClientFrom, ClientTo,User;
		double Amount, BalanceFrom, BalanceTo;
	};
	bool IsEmpty() {
		return (_Mode == enMode::EmpatyMode);
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	string GetAccountNumber() {
		return _AccountNumber;
	}
	void SetPinCode(string pincode) {
		_PinCode = pincode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}
	void SetAccointBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << GetFirstName();
		cout << "\nLastName    : " << GetLastName();
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << GetEmail();
		cout << "\nPhone       : " << GetPhone();
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}
	// Find Client 
	static clsBankClient Find(string AccountNumber) {
		vector<clsBankClient>vClients;
		fstream Myfile;
		Myfile.open("Clients.txt", ios::in);
		if (Myfile.is_open()) {
			string line;
			while (getline(Myfile, line)) {
				clsBankClient client = _ConvetLineToClientObject(line);
				if (client.GetAccountNumber() == AccountNumber) {
					Myfile.close();
					return client;
				}
				vClients.push_back(client);
			}
			Myfile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode) {
		vector<clsBankClient>vClients;
		fstream Myfile;
		Myfile.open("Clients.txt", ios::in);
		if (Myfile.is_open()) {
			string line;
			while (getline(Myfile, line)) {
				clsBankClient client = _ConvetLineToClientObject(line);
				if (client.GetAccountNumber() == AccountNumber && client.GetPinCode() == PinCode) {
					Myfile.close();
					return client;
				}
				vClients.push_back(client);
			}
			Myfile.close();
		}
		return _GetEmptyClientObject();
	}
	enum enSaveResults {svFaildEmptyObject=0,svSucceeded=1, svFaildAccountNumberExist=2};
	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmpatyMode : {
			return enSaveResults::svFaildEmptyObject;
			break;
		}
		case enMode::UpdateMode: {
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode: {
			if (IsClientExist(_AccountNumber)) {
				return enSaveResults::svFaildAccountNumberExist;
			}
			else {
				_AddNewClient();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
				break;
			}
		}
							
		}
	}
	bool Delete() {
		vector<clsBankClient>vClients;
		vClients = _LoadClientsFromFile();
		bool isDeleted = false;

		for (clsBankClient& D : vClients) {
			if (D.GetAccountNumber() == _AccountNumber) {
				D.MarkForDeleted = true;
				isDeleted = true;
			}
		}
		if (isDeleted) {
			_SaveDataToFile(vClients);
			*this = _GetEmptyClientObject();
		}

		return isDeleted;
	}
	static vector<clsBankClient> GetClientsList() {

		return _LoadClientsFromFile();
	}
	static vector<stTransferdata> GetTransferLogsList() {

		return _LoadTransferLogsFromFile();
	}
	static double GetTotalBalances() {
		vector<clsBankClient>vClients = GetClientsList();
		double Balances = 0;
		for (clsBankClient& B : vClients) {
			Balances += B.GetAccountBalance();
		}
		return Balances;
	}
	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount) {
		if (Amount <= _AccountBalance) {
			_AccountBalance -= Amount;
			Save();
			return true;

		}
		return false;

	}
	static bool IsClientExist(string AccountNumber) {
		clsBankClient client = Find(AccountNumber);
		return (!client.IsEmpty());
	}
	bool Transfer(clsBankClient &ClientTo,double Amount) {
		if (this->GetAccountBalance() >= Amount) {
			this->Withdraw(Amount);
			ClientTo.Deposit(Amount);
			_AddDataTransferLogsToFile(_ConverTransferLogsToLine(ClientTo, Amount));
			return true;
		}
		return false;
	}
};

