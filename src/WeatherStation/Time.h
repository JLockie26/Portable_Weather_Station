//Time.h - Interface file for the time class
//--------------------------------------------------------------------
#ifndef Time_H
#define Time_H
//--------------------------------------------------------------------

const int MIN_MINS = 0;
const int MAX_MINS = 59;

const int MIN_HRS = 0;
const int MAX_HRS = 23;

       /**
        *@class Time
        *@brief A class that holds hour and minute values
        *
        *@author Jordan Locke
        *@version 01
        *
        *@author Jordan Locke
        *@version 02
        *@brief Removed Second element from class. Only hours and minutes are needed.
        *       Removal done in order to maintain minimal completion.
        *
        *@version 03
        *@author Jordan Locke
        *@brief Removed Element class. Attributes changed back into raw data types.
        *       Validate method added.
        **/
class Time
{
public:
//Constructors
    Time();
    Time(int newHr, int newMin);

       /**
        *@brief An overloaded assignment operator that assigns the values of another time object to this time
        *@param const Time& otherTime The other time values are being assigned from
        */
const Time& operator=(const Time& otherTime);

//Getters and Setters

       /**
        *@brief Sets minute value
        *@param int newMin
        */
    void setMin(int newMin);

       /**
        *@brief Gets minute value
        *@return int minute
        */
    int getMin() const;

       /**
        *@brief Sets hour value
        *@param int newHr
        */
    void setHr(int newHr);

      /**
        *@brief Gets hour value
        *@return int hour
        */
    int getHr() const;

private:
    int hours;
    int minutes;
    void validate();
};

//--------------------------------------------------------------------
#endif // Time_H
