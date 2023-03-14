// Functions relating to player transactions


#include "player.h"
#include "modifstream.h"
#include "string.h"

modifstream *PlayerTrans::stream = NULL;


//The function reads the next transaction record in the file


PlayerTrans *PlayerTrans::ReadNext()
{
    PlayerTrans *playerTrans;
    char transactionType;
    char a;

    (*stream) >> transactionType;
    if (stream->eof()) 
        throw NoMore();
    if (transactionType == 'A') 
	{
        playerTrans = new EmpTransAdd;
        playerTrans->ReadBody();
        playerTrans->number = -1;
    }
	else if (transactionType == 'C')
	{
        playerTrans = new EmpTransChange;
        (*stream) >> playerTrans->number;
        playerTrans->ReadBody();
    } 
	else if (transactionType == 'D') 
	{
        playerTrans = new EmpTransDelete;
        (*stream) >> playerTrans->number;
    }
	else 
        throw InvalidType();
    do 
	{
        stream->get(a);
    } while ( (!stream->eof()) && (a != '\n') );
    return playerTrans;
}


//Apply a transaction to an player


void PlayerTrans::Apply()
{
}

// Read the data fields of an player record from a transaction file


void PlayerTrans::ReadBody()
{
    char a;

    stream->getquotedstr(name,PlayerNameMax);
    (*stream) >> a;
    if (a == 'G') 
        playerPosition = Guard;
    else if (a == 'G/F') 
        playerPosition = Guard/Forward;
    else if (a == 'F') 
       playerPosition = Forward;
	else if (a == 'F/C')
		playerPosition = Forward/Centre;
	else if (a == 'C')
		playerPosition = Centre;
    else 
        throw InvalidContent();

    (*stream) >> Height;
	(*stream) >> Weight;  ;
    hireDate = stream->getdate();
}


// Prepare to read a transaction file


void PlayerTrans::Open()
{
    if (stream == NULL) 
	{
        stream = new modifstream("playertrans.dat");
        if (stream->bad()) 
		{
			delete stream;
            throw CantOpenFile();
        }
    }
    stream->seekg(0);
}


//Close the player transaction file


void PlayerTrans::Close()
{
    if (stream != NULL) 
	{
        stream->close();
        delete stream;
    }
}


// Apply an "add" transaction record to an Player object


void PlayerTransAdd::Apply()
{
	Player player;

	player.SetHeight(height);
	player.SetWeight(weight);
	player.SetName(name);
	player.SetHireDate(hireDate);
    
    player.Add();
	
}


// Apply a "change" transaction record to an Player object


void PlayerTransChange::Apply()
{
	Player player;
	
	try
	{
		player.Read(number);
	}
	catch(Player::NoSuch) 
	{
	    cerr << endl << "Transaction found for invalid player: " << number;
		throw;
	}


    if (playerPosition != positionEmpty) 
        player.SetPlayerPosition(playerPosition);
	
    if (height != 0) 
        player.SetHeight(Height);
	if (weight != 0)
		player.SetWeight(weight);
		
    if (name[0] != 0) 
        player.SetName(name);
	
    if (hireDate.Year() != 1901) 
        player.SetHireDate(hireDate);
	
    player.Update();

}

//Apply a "delete" transaction record to an Player object


void PlayerTransDelete::Apply()
{
	Player player;
	
	try
	{
		player.Read(number);
	}
	catch(player::NoSuch) 
	{
	    cerr << endl << "Transaction found for invalid player: " << number;
		throw;
	}

	player.SetStatus(EmpStatusInactive);
    
    player.Update();
	
}

