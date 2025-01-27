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

sDate IncreaseDateByXDays(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = IncreaseDateByOneDay(Date);
    }
    
    return Date;
}

sDate IncreaseDateByOneWeek(sDate Date)
{
    return IncreaseDateByXDays(Date, 7);
}

sDate IncreaseDateByXWeeks(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = IncreaseDateByOneWeek(Date);
    }
    
    return Date;
}

sDate IncreaseDateByOneMonth(sDate Date)
{
    if (Date.Month == 12)
    {
        Date.Year++;
        Date.Month = 1;
    }
    else
        Date.Month++;

    //last check day in date should not exceed max days in the current month
    // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should be 28/2/2022
    short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

    if (Date.Day > NumberOfDaysInCurrentMonth)
    {
        Date.Day = NumberOfDaysInCurrentMonth;
    }

    return Date;
}

sDate IncreaseDateByXMonths(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = IncreaseDateByOneMonth(Date);
    }
    return Date;
}

sDate IncreaseDateByOneYear(sDate Date)
{
    Date.Year++;
    return Date;
}

sDate IncreaseDateByXYears(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = IncreaseDateByOneYear(Date);
    }
    return Date;
}

sDate IncreaseDateByXYearsFaster(sDate Date, int X)
{
    Date.Year += X;
    return Date;
}

sDate IncreaseDateByOneDecade(sDate Date)
{
    Date.Year += 10;
    return Date;
}

sDate IncreaseDateByXDecades(sDate Date, int X)
{
    for (int i = 0; i < X; i++)
    {
        Date = IncreaseDateByOneDecade(Date);
    }
    return Date;
}

sDate IncreaseDateByXDecadesFaster(sDate Date, int X)
{
    Date.Year += (X * 10);
    return Date;
}

sDate IncreaseDateByOneCentury(sDate Date)
{
    Date.Year += 100;
    return Date;
}

sDate IncreaseDateByOneMillennium(sDate Date)
{
    Date.Year += 1000;
    return Date;
}

int main()
{
    sDate Date1 = ReadDate(Date1);

    cout << "\nDate After: \n";

    Date1 = IncreaseDateByOneDay(Date1);
    cout << "\n01-Adding one day is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXDays(Date1, 10);
    cout << "\n02-Adding 10 days is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

    Date1 = IncreaseDateByOneWeek(Date1);
    cout << "\n03-Adding one week is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXWeeks(Date1, 10);
    cout << "\n04-Adding 10 weeks is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByOneMonth(Date1);
    cout << "\n05-Adding one month is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXMonths(Date1, 5);
    cout << "\n06-Adding 5 months is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByOneYear(Date1);
    cout << "\n07-Adding one year is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXYears(Date1, 10);
    cout << "\n08-Adding 10 Years is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXYearsFaster(Date1, 10);
    cout << "\n09-Adding 10 Years (faster) is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByOneDecade(Date1);
    cout << "\n10-Adding one Decade is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXDecades(Date1, 10);
    cout << "\n11-Adding 10 Decades is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByXDecadesFaster(Date1, 10);
    cout << "\n12-Adding 10 Decade (faster) is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByOneCentury(Date1);
    cout << "\n13-Adding One Century is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    Date1 = IncreaseDateByOneMillennium(Date1);
    cout << "\n14-Adding One Millennium is: " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    
    system("pause>0");

    return 0; 
}