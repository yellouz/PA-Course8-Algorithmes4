#include<iostream>
using namespace std;

int GetMonth()
{
    int Month;
    cout << "Please Enter a Month Number : ";
    cin >> Month;
    return Month;
}

int GetYear()
{
    int Year;
    cout << "Please Enter a Year : ";
    cin >> Year;
    return Year;
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

int main()
{
    cout << NumberOfDaysInMonth(GetMonth(),GetYear());
}