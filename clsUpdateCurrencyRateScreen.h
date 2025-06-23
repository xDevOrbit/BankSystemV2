#pragma once
#include "clsScreen.h"
class clsUpdateCurrencyRateScreen : protected clsScreen
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
	static void _UpdateRate(clsCurrency& curr) {
		cout << "\n Update Currency Rate : "
			<< "\n---------------------------"
			<< "\n Enter New Rate : ";
		float rr = clsInputValidate::ReadFloatNumber();
		curr.UpdateRate(rr);
	}
public:
	static void ShowUpdateCurrencyRateScreen() {
		_DrawScreenHeader("Update Currency Rate Screen");
		string CurrencyCode;
		cout << "\n Please Enter Currency Code : ";
		CurrencyCode = clsString::UpperAllString(clsInputValidate::ReadString());
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		if (Currency.IsEmpty()) {
			cout << "\n Cant Found Currency .. ";
		}
		else {
			_PrintCurrency(Currency);
			cout << "\n Are You Sure to Update The Rate Currency y/n ";
			char answer = clsInputValidate::ReadChar();
			if (answer == 'y' || answer == 'Y') {
				_UpdateRate(Currency);
				cout << "\n Update Rate Done..:-)";
				_PrintCurrency(Currency);
			}
		}
	}
};

