//Functions relating to player

#include "player.h"

ofstream *Player::out=NULL;
ifstream *Player::in=NULL;
Array<Player::Location> Player::locationList(1);
int Player::locationCount = 0;
int Player::highestNumber = 0;
long Player::highestLocation = 0;


//The Constructor


Player::Player()
{
    memset(name,0,EmpNameMax);;
    number = -1;
    location = -1;
    salaryType = SalTypeSalary;
    salary = 0;
    status = EmpStatusActive;
    hireDate.Set(1901,1,1);
}


//  Open the Player file and build the index


void Player::Open()
{
    Player Player;

    in = new ifstream("Player.dat", ios::in|ios::binary);
	if (in->bad()) 
	{ 
		delete in;
		throw CantOpenFile();
	}
	
    in->seekg(0,ios::beg);
    for (locationCount=0; ; ++locationCount) 
	{
		locationList[locationCount].location = in->tellg();
		try 
		{
			Player.Read();
		}
		catch(EndOfFile) 
		{
			break;
		}
		if (Player.number > highestNumber) 
			highestNumber = Player.number;
		locationList[locationCount].number = Player.number;
	}
	highestLocation = in->tellg();
	in->close();
	delete in;
}


//  Add an Player to the file


void Player::Add()
{

    this->number = locationList[locationCount].number = ++highestNumber;
    location = locationList[locationCount++].location = highestLocation;
    Update();

}


//Read an Player from the file

void Player::Read(int number)
{
	in = new ifstream("Player.dat", ios::in|ios::binary);
	if (in->bad()) 
	{ 
		delete in;
		throw CantOpenFile();
	}

    int i;
	for (i=0; i<locationCount; ++i) 
	{
        if (locationList[i].number == number) 
            break;
    }
    if (i == locationCount) 
        throw NoSuch();
	in->seekg(locationList[i].location,ios::beg);
    Read();
	in->close();
	delete in;
}


//Read an Player from the master file


void Player::Read()
{
	location = in->tellg();
    
	in->read((char *)&number, sizeof(number));
	if (in->gcount() != sizeof(number))
		throw EndOfFile();
	
	in->read((char *)&status, sizeof(status));
	in->read(name, EmpNameMax);
	in->read((char *)&salaryType, sizeof(salaryType));
	in->read((char *)&salary, sizeof(salary));
    hireDate.Read(in);
}


//Write changes in an Player object to the Player file


void Player::Update()
{
	out = new ofstream("Player.dat", ios::in|ios::out|ios::binary);
	if (out->bad())
	{
		delete out;
		throw CantOpenFile();
	}

	out->seekp(location,ios::beg);
	
	out->write((char *)&number, sizeof(number));
	out->write((char *)&status, sizeof(status));
	out->write(name, EmpNameMax);
	out->write((char *)&salaryType, sizeof(salaryType));
	out->write((char *)&salary, sizeof(salary));
    hireDate.Write(out);
	
	highestLocation = out->tellp();
	out->close();
	delete out;
}


//Close the Player file


void Player::Close()
{
}
