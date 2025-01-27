#pragma warning(disable : 4996)

#include<iostream>
#include <ctime>
using namespace std;

struct sDate
{
    int Day;
    int Month;
    int Year;
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
    return (Day == NumberOfDaysInMonth(Month,Year));
}

bool isLastMonthInYear(int Month)
{
    return (Month == 12);
}

bool isLess(sDate Date1, sDate Date2)
{
    if (Date1.Year < Date2.Year)
        return true;
    else
    {
        if (Date1.Year == Date2.Year)
        {
            if (Date1.Month < Date2.Month)
                return true;
            else
            {
                if (Date1.Month == Date2.Month)
                {
                    if (Date1.Day < Date2.Day)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
        }
        else
            return false;
    }

    return true;
}

sDate IncreaseDateByOneDay(sDate Date)
{
    if (isLastDayInMonth(Date.Day, Date.Month, Date.Year))
    {
        if (isLastMonthInYear(Date.Month))
        {
            Date.Day = 1;
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else
    {
        Date.Day++;
    }
    return Date;
}

int DifferenceBetweenTwoDatesInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false)
{
    int NumberOfDays = 0;

    while (isLess(Date1, Date2))
    {
        NumberOfDays++;
        Date1 = IncreaseDateByOneDay(Date1);
    }

    return (IncludeEndDay ? ++NumberOfDays : NumberOfDays);
}

sDate GetSystemDate()
{
    sDate Date;
    time_t t = time(0);
    tm* now = localtime(&t);
    Date.Year = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;
    return Date;
}

int AgeInNumberOfDays(sDate Birthday)
{
    sDate CurrentDay = GetSystemDate();
    return DifferenceBetweenTwoDatesInDays(Birthday, CurrentDay, true);
}

int main()
{
    sDate Birthday = ReadDate(Birthday);
    int AgeInDays = AgeInNumberOfDays(Birthday);
    cout << "Your are " << AgeInDays << " Days old";

    return 0; 
}