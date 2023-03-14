

#include "date.h"

//Sets the current value of the date

void Date::Set(int year,int month,int day)
{
    int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ( (year < 1901) || (year > 2099) ) 
	{
        throw YearOutOfRange();
    }
    this->year = year;

    if (year%4 == 0) 
	{
        months[1] = 29;
    }

    if ( (month < 1) || (month > 12) ) 
	{
        throw MonthOutOfRange();
    }
    this->month = month;

    if ( (day < 1) || (day > months[month-1]) ) 
	{
        throw DayOutOfRange();
    }
    this->day = day;
}


//Read a date from a C-standard stream file


void Date::Read(ifstream *in)
{
	in->read((char *)&year, sizeof(year));
	in->read((char *)&month, sizeof(month));
	in->read((char *)&day, sizeof(day));
}


//  Write a Date object to a C-style stream file


void Date::Write(ofstream *out)
{
    out->write((char *)&year, sizeof(year));
	out->write((char *)&month, sizeof(month));
	out->write((char *)&day, sizeof(day));
}
