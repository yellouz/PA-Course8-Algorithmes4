#include <iostream>
using namespace std;

struct sDate
{
    int Day;
    int Month;
    int Year;
};

struct sPeriod
{
    sDate StartDate;
    sDate EndDate;
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

sPeriod ReadPeriod(sPeriod Period)
{
    Period.StartDate = ReadDate(Period.StartDate);
    Period.EndDate = ReadDate(Period.EndDate);

    return Period;
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

bool isDate1BeforeDate2(sDate Date1, sDate Date2)
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
                }
            }
        }
    }

    return false;
}

bool isDate1EqualDate2(sDate Date1, sDate Date2)
{
    return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
}

bool isDate1AfterDate2(sDate Date1, sDate Date2)
{
   return (!isDate1BeforeDate2(Date1,Date2) && !isDate1EqualDate2(Date1, Date2));
}

short CompareDates(sDate Date1, sDate Date2)
{
    if (isDate1AfterDate2(Date1,Date2))
    {
        return 1;
    }

    if (isDate1BeforeDate2(Date1,Date2))
    {
        return -1;
    }

    if (isDate1EqualDate2(Date1,Date2))
    {
        return 0;
    }
    
}

int DifferenceBetweenTwoDatesInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false)
{
    int NumberOfDays = 0;

    while (isDate1BeforeDate2(Date1, Date2))
    {
        NumberOfDays++;
        Date1 = IncreaseDateByOneDay(Date1);
    }

    return (IncludeEndDay ? ++NumberOfDays : NumberOfDays);
}

int PeriodLengthInDays(sPeriod Period, bool IncludeEndDay = false)
{
    return DifferenceBetweenTwoDatesInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
}

bool isDateWithinPeriod(sPeriod Period, sDate Date)
{
    return !(CompareDates(Date, Period.StartDate) == -1 || CompareDates(Date, Period.EndDate) == 1);
}

bool isPeriodsOverlap(sPeriod Period1, sPeriod Period2)
{
    if (CompareDates(Period2.EndDate, Period1.StartDate) == -1 || CompareDates(Period2.StartDate, Period1.EndDate) == 1)
    {
        return false;
    }

    else 
        return true;
}

int CountOverlapDaysBetweenTwoPeriods(sPeriod Period1, sPeriod Period2)
{
    if (!isPeriodsOverlap(Period1,Period2))
    {
        return 0;
    }
    
    int NumberOfDays = 0;

    while (isDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
    {
        if (isDateWithinPeriod(Period2, Period1.StartDate))
        {
            NumberOfDays++;
        }

        Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
        
    }
    
    return NumberOfDays;
}

int main()
{
    
}