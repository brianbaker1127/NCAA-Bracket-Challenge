#ifndef Team_h
#define Team_h
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
//#include "StatsReader.h"

class Team
{
protected:
	// variables describing the various team stats go here
	double seasonWins; // win percentage
	const char* teamName;
	double seed;
	double ppg;
	double oppg; // opposing teams ppg (measures defense)
	// variables describing the record of wins
	int winCount;
	int CCount;
	int FFCount;
	int EECount;
public:
	Team(const char*,double,double,double,double);
	~Team();

	// methods to output all relevant stats
	const char* GetTeamName() {return teamName;}
	double GetSeasonWins() {return seasonWins;}
	double GetSeed() {return seed;}
	double GetPPG() {return ppg;}
	double GetOPPG() {return oppg;}

	// methods to keep record of wins
		// number of championships won:
	void AddWin() {winCount++;}
	int GetWin() {return winCount;}
		// number of championship game presences
	void AddC() {CCount++;}
	int GetC() {return CCount;}
		//number of final four presences
	void AddFF() {FFCount++;}
	int GetFF() {return FFCount;}
		// number of elite eight presences
	void AddEE() {EECount++;}
	int GetEE() {return EECount;}

};

#endif