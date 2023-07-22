// UnusedCredUiFunction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <wincred.h>
#include <iostream>
#pragma comment(lib,"Credui.lib")
int main()
{
    DWORD dwErr;
    WCHAR szUserName[CREDUI_MAX_USERNAME_LENGTH-1] = {NULL};
    WCHAR szPassword[CREDUI_MAX_PASSWORD_LENGTH-1] = {NULL};
    BOOL fSave;
    DWORD dwAuthError=1223;

    dwErr = CredUICmdLinePromptForCredentials(
        L".",
        NULL,
        dwAuthError,
        (PWSTR)&szUserName,
        sizeof(szUserName),
        (PWSTR)&szPassword,
        sizeof(szPassword),
        &fSave,
        CREDUI_FLAGS_EXPECT_CONFIRMATION|CREDUI_FLAGS_EXCLUDE_CERTIFICATES
    );

    if (dwErr == ERROR_SUCCESS)
    {
        std::wcout << "User Name: " << szUserName << std::endl;
        std::wcout << "Password : " << szPassword << std::endl;
    }
    else if (dwErr == ERROR_CANCELLED)
    {
        std::cout << "User cancelled the operation." << std::endl;
    }
    else
    {
        std::cout << "Error occurred: " << dwErr << std::endl;
    }

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
