#pragma once
#include "clsMainScreen.h"
class clsUpdateClientScreen : protected clsScreen
{
private:
   static void ReadClientInfo(clsBankClient& Client) {
        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccointBalance(clsInputValidate::ReadFloatNumber());
    }

public:

   static void UpdateClientScreen() {
       if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
       {
           return;
       }
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "Cant Found Client Try Again..\n";
            cout << "\nPlease Enter client Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient ClientUpdate = clsBankClient::Find(AccountNumber);
        ClientUpdate.Print();
        cout << "\n Update Info Client.. " + ClientUpdate.FullName() + " ";
        ReadClientInfo(ClientUpdate);
        clsBankClient::enSaveResults resSave;
        resSave = ClientUpdate.Save();
        if (resSave == clsBankClient::enSaveResults::svSucceeded) {
            cout << "\n Update Done ..";
        }
        else if (resSave == clsBankClient::enSaveResults::svFaildEmptyObject) {
            cout << "\n Update Faild .. ";
        }

    }
};

