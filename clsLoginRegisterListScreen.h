#pragma once
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;
class clsLoginRegisterListScreen : protected clsScreen
{
private:
    static void PrintLogsRecordLine(clsUser::stRegisterLoginData Logs)
    {

        cout << "| " << setw(25) << left << Logs.sDate;
        cout << "| " << setw(20) << left << Logs.sUsername;
        cout << "| " << setw(20) << left << Logs.sPassword;
        cout << "| " << setw(15) << left << Logs.sPermission;

    }
public:
    static void ShowLoginRegisterList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLogRegister))
        {
            return;
        }

        vector <clsUser::stRegisterLoginData> vLogs = clsUser::GetLogsList();
        string Title = "\t  Register Login Logs List Screen";
        string SubTitle = "\t    (" + to_string(vLogs.size()) + ") Log(s).";

        _DrawScreenHeader(Title, SubTitle);



        cout << "\n\t\t\t\t\tClient List (" << vLogs.size() << ") Log(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(25) << "Date";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(15) << "Permission";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Logs Available In the System!";
        else

            for (clsUser::stRegisterLoginData cLogs : vLogs)
            {

                PrintLogsRecordLine(cLogs);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

