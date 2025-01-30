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

bool isLeapYear(int Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0);
}

int NumberOfDaysInMonth(int Month, int Year)
{
    if (Month < 1 || Month > 12)
    {
        return 0;
    }

    int NumberOfDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (Month == 2)
    {
        return isLeapYear(Year) ? 29 : 28;
    }
    else
    {
        return NumberOfDays[Month - 1];
    }
}

bool isValidDate(sDate Date)
{
    if (Date.Day < 1 || Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year))
    {
        return false;
    }
    
    if (Date.Month < 1 || Date.Month > 12)
    {
        return false;
    }

    return true;
}

int main()
{
    sDate Date = ReadDate();
    if (isValidDate(Date))
    {
        cout << "Valid";
    }
    else
        cout << "Not Valid";
    
    return 0;
}