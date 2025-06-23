#pragma once
#include "clsMainScreen.h"
class clsFindUserScreen : protected clsScreen
{
public:

    static void ShowFindClientScreen()
    {

        _DrawScreenHeader("\tFind Users Screen");

        string UsersName;
        cout << "\nPlease Enter Username: ";
        UsersName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UsersName))
        {
            cout << "\nUsername is not found, choose another one: ";
            UsersName = clsInputValidate::ReadString();
        }

        clsUser user1 = clsUser::Find(UsersName);

        if (!user1.IsEmpty())
        {
            cout << "\nUsername Found :-)\n";
            user1.Print();
        }
        else
        {
            cout << "\nUsername Was not Found :-(\n";
        }

        

    }
};

