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
                    else
                        return false;
                }
                else
                    return false;
            }
        }
        else
            return false;
    }

    return true;
}

bool isDate1EqualDate2(sDate Date1, sDate Date2)
{
    return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
}

bool isDate1AfterDate2(sDate Date1, sDate Date2)
{
    /*if (Date1.Year > Date2.Year)
        return true;
    else
    {
        if (Date1.Year == Date2.Year)
        {
            if (Date1.Month > Date2.Month)
                return true;
            else
            {
                if (Date1.Month == Date2.Month)
                {
                    if (Date1.Day > Date2.Day)
                        return true;
                }
            }
        }
    }

    return false;
    */
   
   return (!isDate1BeforeDate2(Date1,Date2) && !isDate1EqualDate2(Date1, Date2));
}

int main()
{
    sDate Date1 = ReadDate(Date1);
    sDate Date2 = ReadDate(Date2);

    if (isDate1AfterDate2(Date1,Date2))
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
    return 0;
}