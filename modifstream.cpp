// Functions relating to the "modified" iostream class


#include "modifstream.h"
#include <ctype.h>



//Get a "quoted" string from a stream


char *modifstream::getquotedstr(char *str,int maxlen,char delimit)
{
    char a;

    (*this) >> a;
    
    if (a != delimit) 
        throw InvalidQuotedString();

    char *to = str;
    for ( ; maxlen > 0; --maxlen)
	{
        this->get(*to);
        if (this->eof()) 
            break;
        if (*to == delimit) 
		{
            *to = 0;
            return str;
        }
        if (*to == '\n') 
            throw InvalidQuotedString();
        to++;
    }
    throw MaxLenExceeded();
}

/**********
*
*   Module:     getdate
*
*   Function:   Read a date from the stream
*
**********/

Date modifstream::getdate()
{
    char a;
    int year,month,day;

    (*this) >> year;
    (*this) >> a;
    if (a != '/')
        throw InvalidDate();
    (*this) >> month;
    (*this) >> a;
    if (a != '/') 
        throw InvalidDate();
    (*this) >> day;
    return Date(year,month,day);
}
