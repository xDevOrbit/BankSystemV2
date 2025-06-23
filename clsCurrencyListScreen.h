#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
class clsCurrencyListScreen : protected clsScreen
{
private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << "| " << setw(35) << left << Currency.Country();
        cout << "| " << setw(10) << left << Currency.CurrencyCode();
        cout << "| " << setw(35) << left << Currency.CurrencyName();
        cout << "| " << setw(20) << left << Currency.Rate();
    }
public:
    static void ShowCurrencyList()
    {
        //if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        //{
        //    return;// this will exit the function and it will not continue
        //}

        vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();
        string Title = "\t  Currency List Screen";
        string SubTitle = "\t    (" + to_string(vCurrency.size()) + ") Currency(s).";

        _DrawScreenHeader(Title, SubTitle);



        cout << "\n\t\t\t\t\Currency List (" << vCurrency.size() << ") Currency(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(35) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(35) << "Name";
        cout << "| " << left << setw(20) << "Rate/(1$)";

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrency.size() == 0)
            cout << "\t\t\t\tNo Currency Available In the System!";
        else

            for (clsCurrency Currency : vCurrency)
            {

                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};


