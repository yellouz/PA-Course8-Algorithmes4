#include<iostream>
using namespace std;

bool isLeapYear(int Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0);
}

int main()
{
    int Year = 2000;
    if (isLeapYear(Year))
    {
        cout << Year;
    }
    
}