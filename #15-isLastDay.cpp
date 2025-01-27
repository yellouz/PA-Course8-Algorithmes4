#include<iostream>
using namespace std;

struct sDate
{
    short Day;
    short Month;
    short Year;
};

sDate ReadDate(sDate Date)
{
    cout << "Please Enter a Month Number : ";
    cin >> Date.Month;

    cout << "Please Enter a Year : ";
    cin >> Date.Year;

    cout << "Please Enter a Day : ";
    cin >> Date.Day;

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

bool isLastDayInMonth(int Day, int Month, int Year)
{
    return (Day == NumberOfDaysInMonth(Month,Year) ? true : false);
}

bool isLastMonthInYear(int Month)
{
    return (Month == 12 ? true : false);
}

int main()
{
    sDate Date = ReadDate(Date);

    if (isLastDayInMonth(Date.Day, Date.Month, Date.Year))
    {
        cout << "Yes, the day is the last day of the month \n";
    }
    else
    {
        cout << "No, the day is not the last day of the month \n";
    }

    if (isLastMonthInYear(Date.Month))
    {
        cout << "Yes, the Month is the last Month of the Year \n";
    }
    else
    {
        cout << "No, the Month is not the last Month of the Year \n";   
    }

    return 0;
    
    
    
}