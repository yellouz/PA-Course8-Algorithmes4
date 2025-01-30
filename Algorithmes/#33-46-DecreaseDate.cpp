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

bool isFirstDayInMonth(int Day)
{
    return (Day == 1);
}

bool isFirstMonthInYear(int Month)
{
    return (Month == 1);
}

sDate DecreaseDateByOneDay(sDate Date)
{
    if (isFirstDayInMonth(Date.Day))
    {
        if (isFirstMonthInYear(Date.Month))
        {
            Date.Day = 31;
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
            Date.Month--;
        }
    }
    else
    {
        Date.Day--;
    }
    return Date;
}

sDate DecreaseDateByXDays(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = DecreaseDateByOneDay(Date);
    }
    
    return Date;
}

sDate DecreaseDateByOneWeek(sDate Date)
{
    return DecreaseDateByXDays(Date, 7);
}

sDate DecreaseDateByXWeeks(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = DecreaseDateByOneWeek(Date);
    }
    
    return Date;
}

sDate DecreaseDateByOneMonth(sDate Date)
{
    if (Date.Month == 1)
    {
        Date.Year--;
        Date.Month = 12;
    }
    else
        Date.Month--;

    //last check day in date should not exceed max days in the current month
    // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should be 28/2/2022
    short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

    if (Date.Day > NumberOfDaysInCurrentMonth)
    {
        Date.Day = NumberOfDaysInCurrentMonth;
    }

    return Date;
}

sDate DecreaseDateByXMonths(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}

sDate DecreaseDateByOneYear(sDate Date)
{
    Date.Year--;
    return Date;
}

sDate DecreaseDateByXYears(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = DecreaseDateByOneYear(Date);
    }
    return Date;
}

sDate DecreaseDateByXYearsFaster(sDate Date, int X)
{
    Date.Year -= X;
    return Date;
}

sDate DecreaseDateByOneDecade(sDate Date)
{
    Date.Year -= 10;
    return Date;
}

sDate DecreaseDateByXDecades(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = DecreaseDateByOneDecade(Date);
    }
    return Date;
}

sDate DecreaseDateByXDecadesFaster(sDate Date, int X)
{
    Date.Year -= (X * 10);
    return Date;
}

sDate DecreaseDateByOneCentury(sDate Date)
{
    Date.Year -= 100;
    return Date;
}

sDate DecreaseDateByOneMillennium(sDate Date)
{
    Date.Year -= 1000;
    return Date;
}

int main()
{
    sDate Date1 = ReadDate(Date1);

    cout << "\nDate After: \n";

    Date1 = DecreaseDateByOneDay(Date1);
    cout << "\n01-Decreasing one day is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXDays(Date1, 10);
    cout << "\n02-Decreasing 10 days is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = DecreaseDateByOneWeek(Date1);
    cout << "\n03-Decreasing one week is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXWeeks(Date1, 10);
    cout << "\n04-Decreasing 10 weeks is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByOneMonth(Date1);
    cout << "\n05-Decreasing one month is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXMonths(Date1, 5);
    cout << "\n06-Decreasing 5 months is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByOneYear(Date1);
    cout << "\n07-Decreasing one year is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXYears(Date1, 10);
    cout << "\n08-Decreasing 10 Years is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXYearsFaster(Date1, 10);
    cout << "\n09-Decreasing 10 Years (faster) is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByOneDecade(Date1);
    cout << "\n10-Decreasing one Decade is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXDecades(Date1, 10);
    cout << "\n11-Decreasing 10 Decades is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByXDecadesFaster(Date1, 10);
    cout << "\n12-Decreasing 10 Decade (faster) is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByOneCentury(Date1);
    cout << "\n13-Decreasing One Century is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = DecreaseDateByOneMillennium(Date1);
    cout << "\n14-Decreasing One Millennium is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    system("pause>0");

    return 0; 
}