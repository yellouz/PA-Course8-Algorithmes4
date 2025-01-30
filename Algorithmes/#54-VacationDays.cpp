#include<iostream>
using namespace std;

struct sDate
{
    int Day;
    int Month;
    int Year;
};

sDate ReadDate(sDate Date)
{
    cout << "Please Enter a Day : ";
    cin >> Date.Day;
    
    cout << "Please Enter a Month Number : ";
    cin >> Date.Month;

    cout << "Please Enter a Year : ";
    cin >> Date.Year;

    return Date;
}

int DayOrder(sDate Date)
{
    int a = (14 - Date.Month) / 12;
    int y = Date.Year - a;
    int m = Date.Month + 12 * a - 2;
    //Gregorian Calendar:
    //Sun 0, Mon 1, Tue 2...
    return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
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

bool isEndOfWeek(sDate Date)
{
    int DayOrd = DayOrder(Date);
    return (DayOrd == 6);
    
}

bool isWeekEnd(sDate Date)
{
    int DayOrd = DayOrder(Date);
    return (DayOrd == 5) || (DayOrd == 6);   
}

bool isBusinessDay(sDate Date)
{
    return !isWeekEnd(Date);
}

int DaysUntilEndOfWeek(sDate Date)
{
    return (6 - DayOrder(Date));
}

int DaysUntilEndOfMonth(sDate Date)
{
    return (NumberOfDaysInMonth(Date.Month, Date.Year) - Date.Day);
}

int DaysUntilEndOfYear(sDate Date)
{
    int NumOfDays = DaysUntilEndOfMonth(Date);

    for (int i = Date.Month + 1; i <= 12; i++)
    {
        NumOfDays += NumberOfDaysInMonth(Date.Month, Date.Year);
    }
    return NumOfDays;
}

int VacationDays(sDate VacationStart, sDate VacationEnd)
{
    int NumberOfDays = 0;

    while (isLess(VacationStart, VacationEnd))
    {
        if (!isWeekEnd(VacationStart))
        {
            NumberOfDays++;
        }
        VacationStart = IncreaseDateByOneDay(VacationStart); 
    }

    return NumberOfDays;
}

int main()
{
    sDate VacationStart = ReadDate(VacationStart);
    sDate VacationEnd = ReadDate(VacationEnd);

    cout << "Actual Vacation Days : " << VacationDays(VacationStart, VacationEnd);
    
    return 0;
}