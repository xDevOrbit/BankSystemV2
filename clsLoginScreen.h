#pragma once
#include "clsMainScreen.h"
#include "global.h";
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login() {
		bool LoginFaild = false;
		string Username, Password;
		int FaildLoginCount = 0;
		do {
			if (LoginFaild)
			{
				cout << "\nInvlaid Username/Password!";
				cout << "\nYou have " << (3 - FaildLoginCount)
					<< " Trial(s) to login.\n\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\nYour are Locked after 3 faild trails \n\n";
				return false;
			}
			cout << "Enter Username? ";
			cin >> Username;

			cout << "Enter Password? ";
			cin >> Password;
			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		
	}
public:
	static bool ShowLoginScreen() {
		system("cls");
		
		_DrawScreenHeader("Login Screen");
		return _Login();

	}
};

