//Structures relating to players


#ifndef PLAYER_DEF

#define PLAYER_DEF

const int PlayerNameMax=18;

enum PlayerPosition {
	positionEmpty = -1,
    Guard=0,
	Guard/Forward = 1,
    Forward=2,
	Forward/Centre = 3,
	Centre = 4,
};

enum PlayerStatus{
	PlayerStatusActive=0,
    PlayerStatusInactive=1
};


#include "date.h"
#include "playertrans.h"
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include "array.cpp"
#include "string.h"


class Player {

struct Location {               
    int         number;
    long        location;
};

protected:
	static ofstream *out;
    static ifstream *in;          
    static Array<Location> locationList; 
    static int  locationCount;  
    static int  highestNumber; 
    static long highestLocation;

protected:
    char        name[PlayerNameMaxNameMax];
    long        location;       
    int         number;         
    float        Height;
    float	     Weight;
    PlayerPosition  playerType;
    Date        hireDate;
    playerStatus   status;        

public:

    class       PlayerError { };
	class       NoSuch: public PlayerError { };		
    class       CantOpenFile: public PlayerError { }; 
    class       EndOfFile { };           

public:
                Player();
    void        Read(int number);	    
    void        Add();                 
    void        Remove();               
    void        Update();              
    static void Open();                 
    static void Close();               

    void		SetStatus(PlayerStatus s) { status = s; }
    void        SetHeight (float s){height = s}
	void        SetWeight (float s){weight = s}
	void		SetName(char *n) { strcpy(name,n); }
	void		SetHireDate(Date &date) {	hireDate = date; }

protected:
    void        Read();                
};

#endif
