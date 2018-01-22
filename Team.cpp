#include "Team.h"
#include <iostream>
#include <iomanip>
//#include "StatsReader.h"
#include <cstring>

using namespace std;

Team::Team(const char* teamname, double wins,double r,double PPG, double OPPG)
{
	seasonWins = wins; // when constructed, set all stats
	teamName = teamname;
	seed = r;
	ppg = PPG;
	oppg = OPPG;


	winCount = 0;
	CCount = 0;
	FFCount = 0;
	EECount = 0;
}

Team::~Team()
{

}

