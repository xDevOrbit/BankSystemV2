#pragma once
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;
class clsTransferLogScreen : protected clsScreen
{
private:
    static void PrintLogsRecordLine(clsBankClient::stTransferdata Logs)
    {

        cout << "| " << setw(20) << left << Logs.DateTran;
        cout << "| " << setw(8) << left << Logs.ClientFrom;
        cout << "| " << setw(8) << left << Logs.ClientTo;
        cout << "| " << setw(8) << left << Logs.Amount;
        cout << "| " << setw(10) << left << Logs.BalanceFrom;
        cout << "| " << setw(10) << left << Logs.BalanceTo;
        cout << "| " << setw(8) << left << Logs.User;

    }
public:
    static void ShowTransferLogList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLogRegister))
        {
            return;
        }

        vector <clsBankClient::stTransferdata> vLogs = clsBankClient::GetTransferLogsList();
        string Title = "\t  Transfer Logs List Screen";
        string SubTitle = "\t    (" + to_string(vLogs.size()) + ") Log(s).";

        _DrawScreenHeader(Title, SubTitle);



        cout << "\n\t\t\t\t\tTransfer List (" << vLogs.size() << ") Log(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(20) << "Date";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Logs Available In the System!";
        else

            for (clsBankClient::stTransferdata cLogs : vLogs)
            {

                PrintLogsRecordLine(cLogs);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

