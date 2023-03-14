//Structures relating to the "modified" iostream class


#ifndef MODIFSTREAM_DEF

#define MODIFSTREAM_DEF

#include <fstream.h>
#include "date.h"

class modifstream: public ifstream {

public:
    class MaxLenExceeded { };
    class InvalidQuotedString { };
    class InvalidDate { };

public:
    modifstream(char *name): ifstream(name) { };
    char *getquotedstr(char *str,int maxlen,char delimit='\"');
    Date getdate();
};

#endif
