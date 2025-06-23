#pragma once
#include "clsScreen.h"
class clsDeleteUserScreen :protected clsScreen
{
private:

public:
	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("Delete User Screen");
		string UserName = "";
		cout << "\nPlease Enter client Account Number: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "\n Cant Found UserName";
			cout << "\nPlease Enter client Account Number: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser user1 = clsUser::Find(UserName);
		user1.Print();
		cout << "\nAre you sure you want to delete this client y/n? ";

		char Answer = 'n';
		Answer = clsInputValidate::ReadChar();
		if (Answer == 'Y' || Answer =='y') {
			if (user1.Delete()) {
				cout << "\nUser Deleted Successfully :-)\n";
				user1.Print();
			}
			else {
				cout << "\n Error";
			}
		}
		else {
			cout << "\n Return WithOut Deleted ..";
		}
	}

};

