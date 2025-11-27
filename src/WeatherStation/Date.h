//Date.h - Date class definition / interface

//--------------------------------------------------------------------
#ifndef Date_H
#define Date_H
//--------------------------------------------------------------------

const int MIN_DAYS = 1;
const int MAX_DAYS = 31;

const int MIN_MONTHS = 1;
const int MAX_MONTHS = 12;

const int MIN_YEARS = 1;
const int MAX_YEARS = 9999;

       /**
        *@class Date
        *@brief Holds values that symbolise a date
        *@version 01
        *@version 02 - Adding Date Validation into setter methods
        *@version 03 - Moved member initialisation to constructors. Removed Deconstructor
        *@author Jordan Locke

        *@author Jordan Locke
        *@version 04
        *@brief Re-designed Date class.
        *       Date Class now checks the number of days in a month and if a year is a leap year.
        *       Instead of ints, date values now use element objects, which allows for another layer of validation whilst being abstract.
        *
        *@version 05
        *@author Jordan Locke
        *@brief Removed use of Element class from Date class
        */

class Date{
public:
//Constructors and Destructors
       /**
        *@brief Default constructor for date object
        */
    Date();

       /**
        *@brief Paramaterized constructor for date object
        *@param newDay, newMonth, newYear Values for setting a day, month, and year
        */
    Date(int newDay, int newMonth, int newYear);

       /**
        *@brief An overloaded assignment operator that assigns values of another date to this date
        *@param const Date& otherDate The other date values are being assigned from
        *@return Date
        */
    const Date& operator=(const Date& otherDate);

       /**
        *@brief Sets day
        *@param int newDay for setting day value
        */
    void setDay(int newDay);

       /**
        *@brief Gets day value
        *@return Returns type int
        */
    int getDay() const;

       /**
        *@brief Sets month
        *@param int newMonth for setting month value
        */
    void setMonth(int newMonth);

       /**
        *@brief Gets month value
        *@return Returns type int
        */
    int getMonth() const;

       /**
        *@brief Sets year
        *@param int newYear for setting year value
        */
    void setYear(int newYear);

       /**
        *@brief Gets year value
        *@return Returns type int
        */
    int getYear() const;


private:
    int day;
    int month;
    int year;

       /**
        *@brief Checks the The year value is a leap year
        */
    bool checkLeapYear();

       /**
        *@brief Checks How many days are in a certain month
        */
    void daysInMonth();

       /**
        *@brief Called when the day value exceeds a certain month's day range
        */
    void illegalDay();
};

//--------------------------------------------------------------------
#endif // Date_H

