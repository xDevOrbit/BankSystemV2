#pragma once
#include "clsMainScreen.h"
class clsAddClientScreen : protected clsScreen
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
	static void AddNewClients() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        string Title = "\t  Add New Client Screen";
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount Number Used ...";
            cout << "\nPlease Enter client Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient newClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        ReadClientInfo(newClient);
        clsBankClient::enSaveResults enAddNew;
        enAddNew = newClient.Save();

        if (enAddNew == clsBankClient::svFaildAccountNumberExist) {
            cout << "\n Error..Account Number Used ...";
        }
        else if (enAddNew == clsBankClient::svSucceeded) {
            cout << "\n Added Done ...";
            newClient.Print();
        }

    }
};

