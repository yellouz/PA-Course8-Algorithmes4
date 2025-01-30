#include<iostream>
using namespace std;

int GetYear()
{
    int Year;
    cout << "Please Enter a Year : ";
    cin >> Year;
    return Year;
}

int GetMonth()
{
    int Month;
    cout << "Please Enter a Month Number : ";
    cin >> Month;
    return Month;
}

bool isLeapYear(int Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0);
}

int NumberOfDaysInMonth(int Month, int Year)
{
    switch (Month)
    {
    case 1:
        return 31;
        break;
    
    case 2:
        return (isLeapYear(Year) ? 29 : 28);
        break;

    case 3:
        return 31;
        break;

    case 4:
        return 30;
        break;

    case 5:
        return 31;
        break;

    case 6:
        return 30;
        break;

    case 7:
        return 31;
        break;
    
    case 8:
        return 31;
        break;

    case 9:
        return 30;
        break;

    case 10:
        return 31;
        break;

    case 11:
        return 30;
        break;

    case 12:
        return 31;
        break;

    default:
        break;
    }
    
}

int NumberOfHoursInMonth(int Month, int Year)
{
    return NumberOfDaysInMonth(Month,Year) * 24; 
}

int NumberOfMinutesInMonth(int Month, int Year)
{
    return NumberOfHoursInMonth(Month,Year) * 60;
}

int NumberOfSecondesInMonth(int Month, int Year)
{
    return NumberOfMinutesInMonth(Month,Year) * 60;
}

void PrintDaysHoursMinSec(int Month, int Year)
{
    cout << "\nNumber of Days     in Month [" << Month << "] is " << NumberOfDaysInMonth(Month,Year);
    cout << "\nNumber of Hours    in Month [" << Month << "] is " << NumberOfHoursInMonth(Month,Year);
    cout << "\nNumber of Minutes  in Month [" << Month << "] is " << NumberOfMinutesInMonth(Month,Year);
    cout << "\nNumber of Secondes in Month [" << Month << "] is " << NumberOfSecondesInMonth(Month,Year);
}

int main()
{
    PrintDaysHoursMinSec(GetMonth(),GetYear());
    
}