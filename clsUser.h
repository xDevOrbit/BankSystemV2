#pragma once
// BankSystemV2.cpp : Abdullah -> DevOrBit.dev

#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <string>
#include <vector>
#include <fstream>
#include "clsUtil.h"

using namespace std;
class clsUser : public clsPerson
{
private:
	enum enMode { EmpatyMode = 0, UpdateMode = 1, AddNewMode = 3 };
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool MarkForDeleted = false;
	 struct stRegisterLoginData;

	static clsUser _ConvetLineToClientObject(string line, string Sepretor = "#//#") {
		vector<string>vStrings;
		vStrings = clsString::Split(line, Sepretor);
		return clsUser(enMode::UpdateMode, vStrings[0], vStrings[1], vStrings[2], vStrings[3], vStrings[4], clsUtil::DecryptText(vStrings[5]), stod(vStrings[6]));
	}
	static stRegisterLoginData _ConvetLineToDataLogs(string line, string Sepretor = "#//#") {
		vector<string>vStrings;
		stRegisterLoginData logs;
		vStrings = clsString::Split(line, Sepretor);
		logs.sDate = vStrings[0];
		logs.sUsername = vStrings[1];
		logs.sPassword = vStrings[2];
		logs.sPermission = stoi(vStrings[3]);
		return logs;
			
	}
	static clsUser _GetEmptyClientObject() {
		return clsUser(enMode::EmpatyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadClientsFromFile() {
		vector<clsUser>Users;
		fstream MyFile;
		string line;
		MyFile.open("Users.txt", ios::in);
		while (getline(MyFile, line)) {
			clsUser User = _ConvetLineToClientObject(line);
			Users.push_back(User);
		}
		MyFile.close();
		return Users;
	}
	static string _ConverClientObjectToLine(clsUser Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.GetFirstName() + Seperator;
		stClientRecord += Client.GetLastName() + Seperator;
		stClientRecord += Client.GetEmail() + Seperator;
		stClientRecord += Client.GetPhone() + Seperator;
		stClientRecord += Client.GetUserName() + Seperator;
		stClientRecord += clsUtil::EncryptText(Client.GetPassword()) + Seperator;
		stClientRecord += to_string(Client.GetPermissions());

		return stClientRecord;

	}
	static string _PrepareLogInRecord(clsUser Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += clsDate::GetSystemDateTimeString() + Seperator;
		stClientRecord += Client.GetUserName() + Seperator;
		stClientRecord += Client.GetPassword() + Seperator;
		stClientRecord += to_string(Client.GetPermissions());

		return stClientRecord;

	}
	static void _SaveDataToFile(vector<clsUser> Users) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsUser& C : Users)
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
		vector<clsUser>vUsers;
		vUsers = _LoadClientsFromFile();
		for (clsUser& c : vUsers) {
			if (c.GetUserName() == GetUserName()) {
				c = *this;
				break;
			}
		}
		_SaveDataToFile(vUsers);

	}
	void _AddDataLineToFile(string line) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::app | ios::out);
		if (MyFile.is_open()) {
			MyFile << line << endl;
		}

		MyFile.close();

	}


	void _AddNewClient() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));

	}
	
	static vector<stRegisterLoginData> _LoadLoginLogsFromFile() {
		vector<stRegisterLoginData>vLoginData;
		fstream MyFile;
		string line;
		MyFile.open("Logs.txt", ios::in);
		while (getline(MyFile, line)) {
			stRegisterLoginData ssData = _ConvetLineToDataLogs(line);
			vLoginData.push_back(ssData);
		}
		MyFile.close();
		return vLoginData;
	}
public:
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	static struct stRegisterLoginData {
		string sDate, sUsername, sPassword;
		int sPermission;
	};
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,
		pLogRegister = 128
	};
	bool IsEmpty() {
		return (_Mode == enMode::EmpatyMode);
	}
	static clsUser GetAddNewUserObject(string AccountNumber) {
		return clsUser(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	string GetUserName() {
		return _UserName;
	}
	void SetPassword(string pincode) {
		_Password = pincode;
	}
	string GetPassword() {
		return _Password;
	}
	int GetPermissions() {
		return _Permissions;
	}
	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	void Print()
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << GetFirstName();
		cout << "\nLastName    : " << GetLastName();
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << GetEmail();
		cout << "\nPhone       : " << GetPhone();
		cout << "\nUserName : " << _UserName;
		cout << "\nPassword    : " << _Password;
		cout << "\nPermissions     : " << _Permissions;
		cout << "\n___________________\n";

	}
	// Find vUsers 
	static clsUser Find(string UserName) {
		vector<clsUser>vUsers;
		fstream Myfile;
		Myfile.open("Users.txt", ios::in);
		if (Myfile.is_open()) {
			string line;
			while (getline(Myfile, line)) {
				clsUser user1 = _ConvetLineToClientObject(line);
				if (user1.GetUserName() == UserName) {
					Myfile.close();
					return user1;
				}
				vUsers.push_back(user1);
			}
			Myfile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsUser Find(string UserName, string Password) {
		vector<clsUser>vUsers;
		fstream Myfile;
		Myfile.open("Users.txt", ios::in);
		if (Myfile.is_open()) {
			string line;
			while (getline(Myfile, line)) {
				clsUser user1 = _ConvetLineToClientObject(line);
				if (user1.GetUserName() == UserName && user1.GetPassword() == Password) {
					Myfile.close();
					return user1;
				}
				vUsers.push_back(user1);
			}
			Myfile.close();
		}
		return _GetEmptyClientObject();
	}
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2 };
	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmpatyMode: {
			return enSaveResults::svFaildEmptyObject;
			break;
		}
		case enMode::UpdateMode: {
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode: {
			if (IsUserExist(_UserName)) {
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
		vector<clsUser>Users;
		Users = _LoadClientsFromFile();
		bool isDeleted = false;

		for (clsUser& D : Users) {
			if (D.GetUserName() == _UserName) {
				D.MarkForDeleted = true;
				isDeleted = true;
			}
		}
		if (isDeleted) {
			_SaveDataToFile(Users);
			*this = _GetEmptyClientObject();
		}

		return isDeleted;
	}
	
		static vector<stRegisterLoginData> GetLogsList() {

		return _LoadLoginLogsFromFile();
	}
	static vector<clsUser> GetUsersList() {

		return _LoadClientsFromFile();
	}

	static bool IsUserExist(string UserName) {
		clsUser User1 = Find(UserName);
		return (!User1.IsEmpty());
	}
	bool CheckAccessPermission(enPermissions Permission) {
		if (this->GetPermissions() == enPermissions::eAll) {
			return true;
		}
		else if ((Permission & this->GetPermissions()) == Permission) {
			return true;
		}
		else {
			return false;
		}
	}
	void RegisterLogin() {
		fstream MyFile;
		string line = _PrepareLogInRecord(*this);
		MyFile.open("Logs.txt", ios::app | ios::out);
		if (MyFile.is_open()) {
			MyFile << line << endl;
		}

		MyFile.close();
	}
	
};

