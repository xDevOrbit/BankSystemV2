#pragma once
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsCurrencyListScreen.h"
#include "clsCurrencyFindScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include <iomanip>
using namespace std;
class CurrencyMainScreen : protected clsScreen
{
private:
    enum enCurrencyMenueOptions {
        eListCurrency = 1, eFindCurrency = 2,
        eUpdateCurrency = 3, eCurrencyCalculator = 4, eShowMainMenue = 5
    };

    static short ReadCurrencyMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _ShowListCurrency()
    {
        clsCurrencyListScreen::ShowCurrencyList();
    }

    static void _ShowFindCurrency()
    {
        clsCurrencyFindScreen::ShowCurrencyFind();
    }

    static void _ShowUpdateCurrency()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _ShowCurrencyCalculator()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _GoBackToCurrencyMenue()
    {
        cout << "\n\nPress any key to go back to Currency Menue...";
        system("pause>0");
        ShowCurrencyMenue();

    }

    static void _PerformCurrencyMenueOption(enCurrencyMenueOptions CurrencyMenueOption)
    {
        switch (CurrencyMenueOption)
        {
        case enCurrencyMenueOptions::eListCurrency:
        {
            system("cls");
            _ShowListCurrency();
            _GoBackToCurrencyMenue();
            break;
        }

        case enCurrencyMenueOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrency();
            _GoBackToCurrencyMenue();
            system("pause>0");
            break;
        }

        case enCurrencyMenueOptions::eUpdateCurrency:
        {
            
                system("cls");
                _ShowUpdateCurrency();
            _GoBackToCurrencyMenue();
            system("pause>0");
            break;
        }
        case enCurrencyMenueOptions::eCurrencyCalculator:
        {
             
                system("cls");
                _ShowCurrencyCalculator();
            _GoBackToCurrencyMenue();
            system("pause>0");
            break;
        }



        case enCurrencyMenueOptions::eShowMainMenue:
        {
            //
        }
        }


    }
public:
    static void ShowCurrencyMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t  Currency Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyMenueOption((enCurrencyMenueOptions)ReadCurrencyMenueOption());
    }

};

