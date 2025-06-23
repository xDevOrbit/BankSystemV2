#pragma once  
#include "clsScreen.h"  
using namespace std;  
class clsUpdateUserScreen : protected clsScreen  
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
    static void ShowUpdateUserScreen() {
        _DrawScreenHeader("Update Users Screen");
        string UserName = "";
        cout << "\nPlease Enter User Account Number: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nCant Found User.. ";
            cout << "\nPlease Enter User Account Number: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser user1 = clsUser::Find(UserName);
        user1.Print();
        char Answer = 'n';
        cout << "\nAre you sure you want to update this User y/n? ";
        Answer = clsInputValidate::ReadChar()
            ;        if (Answer == 'Y' || Answer == 'y') {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            ReadUserInfo(user1);
            clsUser::enSaveResults uSave;
            uSave = user1.Save();
            switch (uSave)
            {
            case clsUser::svFaildEmptyObject:
                cout << "\nError User was not saved because it's Empty";
                break;
            case clsUser::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                user1.Print();
                break;
            case clsUser::svFaildAccountNumberExist:
                cout << "\nError User was not saved because it's Faild AccountNumber Exist";
                break;
            }

        }
        else {
            cout << "\nUpdate Cancel";

        }


        
    }
};
