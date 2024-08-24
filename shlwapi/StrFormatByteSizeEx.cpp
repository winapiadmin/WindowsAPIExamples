#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include <windows.h>
#include <shlwapi.h>
int main()
{
    #pragma comment(lib,"shlwapi.lib")
    wstring a(100, L'\0');
    ULONGLONG size;
    cin>>size;
    StrFormatByteSizeEx(size, SFBS_FLAGS_ROUND_TO_NEAREST_DISPLAYED_DIGIT, &a[0], 100);
    wcout << "SFBS_FLAGS_ROUND_TO_NEAREST_DISPLAYED_DIGIT (" << size <<" bytes): " << a << endl;
    StrFormatByteSizeEx(size, SFBS_FLAGS_TRUNCATE_UNDISPLAYED_DECIMAL_DIGITS, &a[0], 100);
    wcout << "SFBS_FLAGS_TRUNCATE_UNDISPLAYED_DECIMAL_DIGITS (" << size <<" bytes): " << a << endl;

    return 0;
}
