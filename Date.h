
#ifndef DATE_DEF

#define DATE_DEF

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>


class Date {

protected:
    int         year;
    int         month;
    int         day;

public:
    class       DateErrors { };
    class       OutOfRange: public DateErrors { };
    class       YearOutOfRange: public OutOfRange { };
    class       MonthOutOfRange: public OutOfRange { };
    class       DayOutOfRange: public OutOfRange { };
    class       EndOfFile { };
    class       DiskFull { };

public:
                Date(int year,int month=1,int day=1)
                    { Set(year,month,day); }
                Date()
                    { year=1900; month=1; day=1; }
    int         Year()
                    { return year; }
    int         Month()
                    { return month; }
    int         Day()
                    { return day; }
    void        Set(int year,int month=1,int day=1);
    void        Read(ifstream *in);
    void        Write(ofstream *out);
};

#endif
