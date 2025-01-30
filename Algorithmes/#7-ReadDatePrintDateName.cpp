#include<iostream>
using namespace std;

enum enDayName { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

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

void PrintDayName(int Day, int Month, int Year)
{
    int a = (14 - Month) / 12;
    int y = Year - a;
    int m = Month + 12 * a - 2;
    //Gregorian Calendar:
    int d = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
    string DayName;

    switch (d)
    {
    case enDayName::Sunday:
        DayName = "Sunday";
        break;
    
    case enDayName::Friday:
        DayName = "Friday";
        break;

    case enDayName::Monday:
        DayName = "Monday";
        break;

    case enDayName::Tuesday:
        DayName = "Tuesday";
        break;

    case enDayName::Wednesday:
        DayName = "Wednesday";
        break;

    case enDayName::Thursday:
        DayName = "Thusday";
        break;

    case enDayName::Saturday:
        DayName = "Saturday";
        break;

    default:
        break;
    }

    cout << DayName << endl;
}

int main()
{
    PrintDayName(GetDay(),GetMonth(),GetYear());
}