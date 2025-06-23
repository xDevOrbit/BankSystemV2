#pragma once
#include "clsScreen.h"
class clsCurrencyFindScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency curr) {
		cout << "\n-------------------------------"
			<< "\nCountry : " + curr.Country()
			<< "\nCode : " + curr.CurrencyCode()
			<< "\nName : " + curr.CurrencyName()
			<< "\nRate(1$)" + to_string(curr.Rate())
			<< "\n-------------------------------";
	}
public:
	static void ShowCurrencyFind() {
		_DrawScreenHeader("Currency Find Screen");
		int FindBy; string Findtext;
		cout << "\nFind By [1] Code Or [2] Country ? ";
		FindBy = clsInputValidate::ReadShortNumberBetween(1, 2);
		if (FindBy == 1) {
			cout << "\nPlease Enter Currency Code : ";
			Findtext = clsString::UpperAllString(clsInputValidate::ReadString());
			//while (!clsCurrency::IsCurrencyCodeExist(Findtext)) {
			//	cout << "Cant Found..";
			//	cout << "\nPlease Enter Currency Code : ";
			//	clsString::UpperAllString(Findtext) = clsInputValidate::ReadString();
			//	
			//}
			clsCurrency curr = clsCurrency::FindByCode(Findtext);
			if (!curr.IsEmpty()) {
				cout << "\n Currency Found :-)";
				_PrintCurrency(curr);
			}
			else {
				cout<< "\nCant Found..";
			}


		}
		else if (FindBy == 2) {
			cout << "\nPlease Enter Contry Name : ";
			Findtext = clsString::UpperAllString(clsInputValidate::ReadString());
			clsCurrency curr = clsCurrency::FindByCountry(Findtext);
			if (!curr.IsEmpty()) {
				cout << "\n Currency Found :-)";
				_PrintCurrency(curr);
			}
			else {
				cout << "\nCant Found..";
			}

		}
	}
};

