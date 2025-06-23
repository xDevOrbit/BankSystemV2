#pragma once
#include "clsMainScreen.h"
class clsDeleteClientScreen :protected clsScreen
{
public:
   static void DeleteMainScreen() {
       if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
       {
           return;
       }
        _DrawScreenHeader("\tDelete Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            string AccountNumber = "";
            cout << "\nPlease Enter client Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient deleteclient = clsBankClient::Find(AccountNumber);
        deleteclient.Print();
        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y') {
            if (deleteclient.Delete()) {
                cout << "\n Done Delete Account ..";
                deleteclient.Print();
            }
            else {
                cout << "\nCant Deleted Account  ..." << endl;

            }
        }


    }
};

