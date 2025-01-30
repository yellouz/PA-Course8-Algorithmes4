#include <iostream>
using namespace std;

struct sDate
{
    int Day;
    int Month;
    int Year;
};

sDate ReadDate()
{
    sDate Date;

    cout << "Please Enter a Day : ";
    cin >> Date.Day;
    
    cout << "Please Enter a Month Number : ";
    cin >> Date.Month;

    cout << "Please Enter a Year : ";
    cin >> Date.Year;

    return Date;
}

sDate StringToDate(string StringDate)
{
    string tmp[3] = {"","",""};
    int j = 0;

    for (int i = 0; i < StringDate.length(); i++)
    {
        if (StringDate[i] == '/')
        {
            j++;
            continue;
        }

        tmp[j] += StringDate[i];
    }

    sDate Date;
    Date.Day = stoi(tmp[0]);
    Date.Month = stoi(tmp[1]);
    Date.Year = stoi(tmp[2]);

    return Date;
}

string DateToString(sDate Date)
{
    string StringDate = "";
    StringDate += to_string(Date.Day);
    StringDate += '/';
    StringDate += to_string(Date.Month);
    StringDate += '/';
    StringDate += to_string(Date.Year);

    return StringDate;
}

int main()
{
    string StringDate;
    cout << "Enter The Date : ";
    cin >> StringDate;

    sDate Date = StringToDate(StringDate);
    cout << Date.Day << endl;
    cout << Date.Month << endl;
    cout << Date.Year << endl;

    cout << DateToString(Date);

    return 0;
}