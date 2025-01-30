#include<iostream>
using namespace std;

int GetYear()
{
    int Year;
    cout << "Please Enter a Year : ";
    cin >> Year;
    return Year;
}

bool isLeapYear(int Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0);
}

void PrintDaysHoursMinSec(int Year)
{
    int Days;
    int Hours;
    int Minutes;
    int Secondes;

    Days = isLeapYear(Year) ? 366 : 365;
    Hours = 24 * Days;
    Minutes = 60 * Hours;
    Secondes = 60 * Minutes;

    cout << "\nNumber of Days     in Year [" << Year << "] is " << Days;
    cout << "\nNumber of Hours    in Year [" << Year << "] is " << Hours;
    cout << "\nNumber of Minutes  in Year [" << Year << "] is " << Minutes;
    cout << "\nNumber of Secondes in Year [" << Year << "] is " << Secondes;

}

int main()
{
    PrintDaysHoursMinSec(GetYear());
    
}