// BankSystemV2.cpp : Abdullah -> DevOrBit.dev

#include <iostream>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
using namespace std;

int main()
{

    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }

    }

    return 0;
}

