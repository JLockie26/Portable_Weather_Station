//Date.cpp - Date class implementation
//--------------------------------------------------------------------
#include "Date.h"
//--------------------------------------------------------------------

//Constructors
Date::Date(): day(1), month(1), year(1)
{

}

Date::Date(int newDay, int newMonth, int newYear): day(newDay), month(newMonth), year(newYear)
{
    day = newDay;
    month = newMonth;
    year = newYear;
    daysInMonth();
}

//Assignment Operator
const Date& Date::operator=(const Date& otherDate)
{
    if(this != &otherDate) //Avoid self assignment
    {
        day = otherDate.day;
        month = otherDate.month;
        year = otherDate.year;
    }

    return *this;
}

//Getters and Setters
void Date::setDay(int newDay)
{
    day = newDay;
}

int Date::getDay() const
{
    return day;
}

void Date::setMonth(int newMonth)
{
    month = newMonth;
}

int Date::getMonth() const
{
    return month;
}

void Date::setYear(int newYear)
{
    year = newYear;
    daysInMonth();
}

int Date::getYear() const
{
    return year;
}

//Other / Behaviour Methods
bool Date::checkLeapYear()
{
    /*
    A leap year is perfectly divisible by 4
    Century years like 2000 are only leap years if perfectly divisible by 400
    */
    if(year % 400 == 0 || (year % 100 && year % 4 == 0))
        return true;

    else
        return false;
}

void Date::daysInMonth()
{
    /*
    "30 days has September, April, June, and November.
     All the rest have 31, except February, which has 28 or 29 on a leap year"
     - My Primary School Teacher
    */
    switch(month)
    {
    case 2:
        if(checkLeapYear() && day >= 29)
            day = 29;

        else if(!checkLeapYear() && getDay() > 28)
            day = 28;

        break;

    case 4:
        illegalDay();
        break;

    case 6:
        illegalDay();
        break;

    case 9:
        illegalDay();
        break;

    case 11:
        illegalDay();
        break;

    default:
        if(day > 31)
            day = 31;

    }
}

void Date::illegalDay()
{
    //Saves writing this if statement constantly
    if(day > 30)
        day = 30;
}

//--------------------------------------------------------------------
