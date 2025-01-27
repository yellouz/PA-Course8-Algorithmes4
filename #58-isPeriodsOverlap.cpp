#include<iostream>
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

bool isPeriodsOverlap(sPeriod Period1, sPeriod Period2)
{
    /*
    if (CompareDates(Period1.StartDate, Period2.StartDate) == 1 && CompareDates(Period1.EndDate, Period2.EndDate) == 1)
    {
        return true;
    }

    if (CompareDates(Period1.StartDate, Period2.StartDate) == -1 && CompareDates(Period1.EndDate, Period2.EndDate) == -1)
    {
        return true;
    }

    if (CompareDates(Period1.StartDate, Period2.StartDate) == 1 && CompareDates(Period1.EndDate, Period2.EndDate) == -1)
    {
        return true;
    }

    if (CompareDates(Period1.StartDate, Period2.StartDate) == -1 && CompareDates(Period1.EndDate, Period2.EndDate) == 1)
    {
        return true;
    }

    if (CompareDates(Period1.StartDate, Period2.StartDate) == 1 && CompareDates(Period1.StartDate, Period2.EndDate) == 0)
    {
        return true;
    }

    if (CompareDates(Period1.StartDate, Period2.StartDate) == -1 && CompareDates(Period1.EndDate, Period2.StartDate) == 0)
    {
        return true;
    }
    
    return false;
    */

    //if (CompareDates(Period1.StartDate, Period2.StartDate) == CompareDates(Period1.EndDate, Period2.EndDate));
    if (CompareDates(Period2.EndDate, Period1.StartDate) == -1 || CompareDates(Period2.StartDate, Period1.EndDate) == 1)
    {
        return false;
    }

    else 
        return true;
   
}

int main()
{
    cout << "Period 1 : \n";
    sPeriod Period1 = ReadPeriod(Period1);
    cout << "Period 2 : \n";
    sPeriod Period2 = ReadPeriod(Period2);

    cout << "Compare Result : " << isPeriodsOverlap(Period1, Period2);

    return 0;
}