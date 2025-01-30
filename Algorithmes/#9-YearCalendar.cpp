#include<iostream>
using namespace std;

int GetYear()
{
    int Year;
    cout << "Please Enter a Year : ";
    cin >> Year;
    return Year;
}

int DayOrder(int Day, int Month, int Year)
{
    int a = (14 - Month) / 12;
    int y = Year - a;
    int m = Month + 12 * a - 2;
    //Gregorian Calendar:
    //Sun 0, Mon 1, Tue 2...
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
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

string MonthShortName(short MonthNumber)
{
    string Months[12] = { "Jan", "Feb", "Mar",
    "Apr", "May", "Jun",
    "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"
    };

    return (Months[MonthNumber - 1]);
}

void PrintMonthCalendar(int Year, int Month)
{
    int FirstDayOfMonth = DayOrder(1,Month,Year);
    int NumberOfDays = NumberOfDaysInMonth(Month,Year);

    cout << "\n_________________________" << MonthShortName(Month) << "_____________________________" << endl;
    printf("Sun \t Mon \t Tue \t Wed \t Thu \t Fri \t Sat \n");

    int i;
    for ( i = 0; i < FirstDayOfMonth; i++)
    {
        cout << " \t ";
    }
    
    for (int j = 1; j <= NumberOfDays; j++)
    {
        cout << j << " \t ";
        if (++i % 7 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}

void PrintYearCalendar(int Year)
{
    cout << "\n_________________________________________________________\n";
    cout << "                      Calendar - " << Year;
    cout << "\n_________________________________________________________\n";


    for (int Month = 1; Month < 12; Month++)
    {
        PrintMonthCalendar(Year,Month);
    }
    
}

int main()
{
    PrintYearCalendar(GetYear());
}