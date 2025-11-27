//Time.cpp - Implementation file of Time Class
//--------------------------------------------------------------------
#include "Time.h"
//--------------------------------------------------------------------

//Constructors
Time::Time(): hours(0), minutes(0)
{

}

Time::Time(int newHr, int newMin): hours(newHr), minutes(newMin)
{
    hours = newHr;
    minutes = newMin;
    validate();
}

//Overloaded Assignment Operator
const Time& Time::operator=(const Time& otherTime)
{
    if(this != &otherTime)
    {
        hours = otherTime.hours;
        minutes = otherTime.minutes;
    }

    return *this;
}

//Getter and Setters}

//Minutes
void Time::setMin(int newMin)
{
    minutes = newMin;
    validate();
}

int Time::getMin() const
{
    return minutes;
}

//Hours
void Time::setHr(int newHr)
{
    hours = newHr;
    validate();
}

int Time::getHr() const
{
    return hours;
}

//Validate
void Time::validate()
{
    if(hours < MIN_HRS || hours > MAX_HRS)
        hours = MIN_HRS;

    if(minutes < MIN_MINS || minutes > MAX_MINS)
        minutes = MIN_MINS;

}

//--------------------------------------------------------------------
