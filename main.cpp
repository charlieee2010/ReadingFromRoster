#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include "player.h"


int main()
{
	//declare a pointer to a PlayerTrans object
    PlayerTrans     *playerTrans;
	try
	{
		Player::Open();
		PlayerTrans::Open();
	}
	catch(Player::CantOpenFile)
	{
		return 1;
	}
	catch(PlayerTrans::CantOpenFile)
	{
		return 1;
	}
	/*
	 reads data from the PlayerTrans file using the ReadNext method 
	 of the PlayerTrans class. 
	 It then applies the data using the Apply method of the PlayerTrans class,
	 and then deallocates the memory allocated for the playerTrans
	 object using the delete operator
	*/
	
	
    for (;;) 
	{
		try 
		{
			playerTrans = PlayerTrans::ReadNext();
			playerTrans->Apply();
			delete playerTrans;
		}
		catch(PlayerTrans::NoMore) 
		{
			break;
		}
		catch(Player::NoSuch) 
		{
			break;
		}
    }
    Player::Close();
    PlayerTrans::Close();
	return 0;
}
