#include<iostream>
#include<ctime>
using namespace std;

enum enDayName { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

struct sDate
{
    int Day;
    int Month;
    int Year;
};

int DayOrder(sDate Date)
{
    int a = (14 - Date.Month) / 12;
    int y = Date.Year - a;
    int m = Date.Month + 12 * a - 2;
    //Gregorian Calendar:
    //Sun 0, Mon 1, Tue 2...
    return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
}

string DayShortName(int d)
{
    string DayName;
    switch (d)
    {
    case enDayName::Sunday:
        DayName = "Sun";
        break;
    
    case enDayName::Friday:
        DayName = "Fri";
        break;

    case enDayName::Monday:
        DayName = "Mon";
        break;

    case enDayName::Tuesday:
        DayName = "Tue";
        break;

    case enDayName::Wednesday:
        DayName = "Wed";
        break;

    case enDayName::Thursday:
        DayName = "Thu";
        break;

    case enDayName::Saturday:
        DayName = "Sat";
        break;

    default:
        break;
    }
    return DayName;
}

string MonthShortName(short MonthNumber)
{
    string Months[12] = { "Jan", "Feb", "Mar",
    "Apr", "May", "Jun",
    "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"
    };

    return (Months[MonthNumber - 1]);
}

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

int main()
{
    sDate Date1 = GetSystemDate();

    cout << "\nToday is " << DayShortName(DayOrder(Date1)) << " , " << Date1.Day << "/" << Date1.Month << "/" << Date1.Year << endl;
    //---------------------
    cout << "\nIs it End of Week?\n";
    if (isEndOfWeek(Date1))
        cout << "Yes it is Saturday, it's of Week.";
    else
        cout << "No it's Not end of week.";
    //---------------------
    cout << "\n\nIs it Weekend?\n";
    if (isWeekEnd(Date1))
        cout << "Yes it is a week end.";
    else
        cout << "No today is " << DayShortName(DayOrder(Date1)) << ", Not a weekend.";
    //---------------------
    cout << "\n\nIs it Business Day?\n";
    if (isBusinessDay(Date1))
        cout << "Yes it is a business day.";
    else
        cout << "No it is NOT a business day.";
    //---------------------
    cout << "\n\nDays until end of week : " << DaysUntilEndOfWeek(Date1) << " Day(s).";
    //---------------------
    cout << "\nDays until end of month : " << DaysUntilEndOfMonth(Date1) << " Day(s).";
    //---------------------
    cout << "\nDays until end of year : " << DaysUntilEndOfYear(Date1) << " Day(s).";

    system("pause>0");

    return 0;
}
