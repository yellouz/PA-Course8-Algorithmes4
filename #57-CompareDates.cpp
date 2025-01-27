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

int main()
{
    sDate Date1 = ReadDate(Date1);
    sDate Date2 = ReadDate(Date2);

    cout << "Compare Result : " << CompareDates(Date1, Date2);

    return 0;
}