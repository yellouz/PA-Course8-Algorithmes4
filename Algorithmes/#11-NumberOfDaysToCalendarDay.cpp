#include<iostream>
using namespace std;

struct sDate
{
    short Day;
    short Month;
    short Year;
};

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

int GetDay()
{
    int Day;
    cout << "Please Enter a Day : ";
    cin >> Day;
    return Day;
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

int TotalDaysFromBeginnigOfTheYear(int Day, int Month, int Year)
{
    int NumberOfDays = 0;

    for (int i = 1; i < Month; i++)
    {
        NumberOfDays += NumberOfDaysInMonth(i, Year);
    }

    NumberOfDays += Day;

    return NumberOfDays;
}

sDate NumberOfDaysToCalendarDay(int NumberOfDays, int Year)
{
    short Month = 1;
    short Day = 0;

    while (NumberOfDays != 0)
    {
        NumberOfDays--;
        Day++;

        if (Day == NumberOfDaysInMonth(Month, Year))
        {
            Month++;
            Day = 0;
        }
    }
    sDate Date;
    Date.Day = Day;
    Date.Month = Month;
    Date.Year = Year;

    return Date;
}

int main()
{
    short Day = GetDay();
    short Month = GetMonth();
    short Year = GetYear();

    short NumberOfDays = TotalDaysFromBeginnigOfTheYear(Day, Month, Year);
    cout << "Number of Days since the beginnig of the year : " << NumberOfDays << endl;

    sDate Date = NumberOfDaysToCalendarDay(NumberOfDays, Year);
    cout << "Date for [" << NumberOfDays << "] is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    return 0;
}