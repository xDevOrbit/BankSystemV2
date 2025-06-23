#pragma once
#include "clsScreen.h"
class AddNewUserScreen : protected clsScreen
{
private:
    static void ReadUserInfo(clsUser& User) {
        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.SetPassword(clsInputValidate::ReadString());
        User.SetPermissions(_ReadPermissionsToSet());
    }
    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer;
        cout << "\nDo you want to give full access? y/n? ";
        Answer = clsInputValidate::ReadChar();
        if (Answer == 'y' || Answer == 'Y') {
            Permissions = clsUser::enPermissions::eAll;
        }
        else {
            cout << "\nDo you want to give access to : \n ";

            cout << "\nShow Client List? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pListClients;
            }
            cout << "\nAdd New Client? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pAddNewClient;
            }
            cout << "\nDelete Client? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pDeleteClient;
            }
            cout << "\nUpdate Client? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pUpdateClients;
            }
            cout << "\nFind Client? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pFindClient;
            }
            cout << "\nTransactions? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pTranactions;
            }
            cout << "\nManage Users? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pManageUsers;
            }
            cout << "\nLogin Register Logs? y/n? ";
            Answer = clsInputValidate::ReadChar();
            if (Answer == 'y' || Answer == 'Y') {
                Permissions += clsUser::enPermissions::pLogRegister;
            }
        }
        return Permissions;

    }
            

    
public:
    
	static void ShowAddNewUserScreen() {
        _DrawScreenHeader("\t  Add New User Screen");
        string UserName = "";
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName)) {
            cout << "\n UserName IS Used Plase Try !!..";
            cout << "\nPlease Enter UserName: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser user1 = clsUser::GetAddNewUserObject(UserName);
        ReadUserInfo(user1);

        clsUser::enSaveResults SaveAdd;
        SaveAdd = user1.Save();
        if (SaveAdd == clsUser::enSaveResults::svSucceeded) {
            cout << "\n Added User Done ...";
            user1.Print();
        }
        else if(SaveAdd == clsUser::enSaveResults::svFaildAccountNumberExist) {
            cout << "\n UserName Used ..";
        }
        else {
            cout << "\n Cant add -Error- ";
        }

	}
};

