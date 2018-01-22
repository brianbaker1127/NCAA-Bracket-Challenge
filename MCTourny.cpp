// Created by Brian Baker: bbaker.1796@gmail.com
// December 2016


// This C++ script simulates NCAA March Madness Tournaments
// using a Monte Carlo approach. Victorious teams are chosen randomly based on
// outside statistics. Teams are more likely to win if they have better stats. 
// The output of this simulation are 6 .dat files giving the bracket results, organized
// according to round winners (e.g. the sweet sixteen winners are stored in their own file)

#include <iostream>
#include <stdlib.h>
#include <vector> 
#include <iomanip>
#include <ctime>
#include "Team.h"
#include "Team.cpp"
#include <time.h>
#include <fstream>

using namespace std;



void RoundOne(vector<Team*>&,vector<Team*>&);
void RoundTwo(vector<Team*>&,vector<Team*>&);
void SweetSixteen(vector<Team*>&,vector<Team*>&);
void EliteEight(vector<Team*>&,vector<Team*>&);
void FinalFour(vector<Team*>&,vector<Team*>&);
void Championship(vector<Team*>&,vector<Team*>&);
Team* game(Team*,Team*);

int main()
{
	int N;
	cout << "Choose how many tournaments to simulate: " << endl;
	cin >> N;
	// The main program will be responsible for the primary simulation
	vector<Team*> AllTeams;
	vector<Team*> roundtwoTeams;
	vector<Team*> sweetsixteenTeams;
	vector<Team*> eliteeightTeams;
	vector<Team*> finalfourTeams;
	vector<Team*> championshipTeams;
	vector<Team*> WINNER;
	// allocate space to store teams and team winners

	// Load all teams (order: South - West - East - MidWest)
	AllTeams.push_back(new Team("Kansas",.882,1,81.3,67.6));
	AllTeams.push_back(new Team("AustinPeay",.514,16,76.1,76.8));
	AllTeams.push_back(new Team("Colorado",.667,8,75.8,70.8));
	AllTeams.push_back(new Team("Connecticut",.706,9,73.1,63.5));
	AllTeams.push_back(new Team("Maryland",.758,5,75.7,66.7));
	AllTeams.push_back(new Team("SouthDakotaSt.",.757,12,68.6,60.6));
	AllTeams.push_back(new Team("California",.697,4,74.9,67.3));
	AllTeams.push_back(new Team("Hawaii",.844,13,77.1,66.7));
	AllTeams.push_back(new Team("Arizona",.758,6,80.4,68.9));
	AllTeams.push_back(new Team("WichitaState",.758,11,72.4,59.));
	AllTeams.push_back(new Team("Miami(Fla.)",.781,3,75.2,67.4));
	AllTeams.push_back(new Team("Buffalo",.588,14,77.4,75.3));
	AllTeams.push_back(new Team("Iowa",.677,7,77.6,69.3));
	AllTeams.push_back(new Team("Temple",.656,10,68.7,67.6));
	AllTeams.push_back(new Team("Villanova",.853,2,78,63.6));
	AllTeams.push_back(new Team("UNCAsheville",.667,15,75.1,68));
	AllTeams.push_back(new Team("Oregon",.824,1,78.7,68.8));
	AllTeams.push_back(new Team("HolyCross",.441,16,64.8,69.9));
	AllTeams.push_back(new Team("SaintJosephs",.794,8,77.2,70.1));
	AllTeams.push_back(new Team("Cincinnati",.688,9,73.3,63.3));
	AllTeams.push_back(new Team("Baylor",.667,5,77.1,69.6));
	AllTeams.push_back(new Team("Yale",.786,12,74.9,63.8));
	AllTeams.push_back(new Team("Duke",.697,4,81.1,72.5));
	AllTeams.push_back(new Team("UNCW",.781,13,79.4,72.1));
	AllTeams.push_back(new Team("Texas",.625,6,71.4,68.3));
	AllTeams.push_back(new Team("UNI",.647,11,68.8,64));
	AllTeams.push_back(new Team("TexasA&M",.765,3,76.4,66.4));
	AllTeams.push_back(new Team("GreenBay",.657,14,83.7,80));
	AllTeams.push_back(new Team("OregonState",.613,7,71.9,70.1));
	AllTeams.push_back(new Team("VCU",.706,10,77.3,67.8));
	AllTeams.push_back(new Team("Oklahoma",.781,2,79.7,71.1));
	AllTeams.push_back(new Team("CSUBakersfield",.75,15,72.9,63.8));
	AllTeams.push_back(new Team("NorthCarolina",.824,1,70,70));
	AllTeams.push_back(new Team("FGCU",.618,16,77.2,70.7));
	AllTeams.push_back(new Team("USC",.636,8,80.5,74.6));
	AllTeams.push_back(new Team("Providence",.697,9,73.6,70.1));
	AllTeams.push_back(new Team("Indiana",.781,5,82.6,69.9));
	AllTeams.push_back(new Team("Chattanooga",.853,12,75.8,67.5));
	AllTeams.push_back(new Team("Kentucky",.765,4,79.5,68.1));
	AllTeams.push_back(new Team("StonyBrook",.813,13,76.2,64.1));
	AllTeams.push_back(new Team("NotreDame",.656,6,75.1,70.6));
	AllTeams.push_back(new Team("Michigan",.657,11,73.8,67.4));
	AllTeams.push_back(new Team("WestVirginia",.765,3,78.5,66.7));
	AllTeams.push_back(new Team("StephFAustin",.848,14,80.2,66.3));
	AllTeams.push_back(new Team("Wisconsin",.625,7,67.8,63.8));
	AllTeams.push_back(new Team("Pittsburgh",.656,10,75,67.3));
	AllTeams.push_back(new Team("Xavier",.844,2,80.5,70.4));
	AllTeams.push_back(new Team("WeberSt.",.765,15,76.1,67));
	AllTeams.push_back(new Team("Virginia",.788,1,71,60.1));
	AllTeams.push_back(new Team("Hampton",.677,16,73.8,74.1));
	AllTeams.push_back(new Team("TexasTech",.613,8,72,69.9));
	AllTeams.push_back(new Team("Butler",.677,9,79.9,71));
	AllTeams.push_back(new Team("Purdue",.765,5,77.9,65.2));
	AllTeams.push_back(new Team("LittleRock",.879,12,71.1,60.8));
	AllTeams.push_back(new Team("IowaState",.656,4,81.8,75));
	AllTeams.push_back(new Team("Iona",.688,13,79.6,74.3));
	AllTeams.push_back(new Team("SetonHall",.758,6,74.2,67.8));
	AllTeams.push_back(new Team("Gonzaga",.788,11,78.9,65.6));
	AllTeams.push_back(new Team("Utah",.765,3,77.2,69.5));
	AllTeams.push_back(new Team("FresnoState",.735,14,75.1,70.7));
	AllTeams.push_back(new Team("Dayton",.800,7,72.5,65.9));
	AllTeams.push_back(new Team("Syracuse",.594,10,70,65.1));
	AllTeams.push_back(new Team("MichiganState",.853,2,79.8,64.1));
	AllTeams.push_back(new Team("MiddleTenn.",.727,15,72.5,68.9));
	

	//********* loop over tournaments:
	srand(time(NULL));
	int count = 0;
	ofstream ROUNDONEWINNERS;
	ofstream ROUNDTWOWINNERS;
	ofstream SSWINNERS;
	ofstream EEWINNERS;
	ofstream FFWINNERS;
	ofstream CHAMP;
	ofstream champDist; // contains all teams and their championship count
	ofstream CDist;
	ofstream FFDist;
	ofstream EEDist;
	ROUNDONEWINNERS.open("RoundOneWinners.dat");
	ROUNDTWOWINNERS.open("RoundTwoWinners.dat");
	SSWINNERS.open("SSWinners.dat");
	EEWINNERS.open("EEWinners.dat");
	FFWINNERS.open("FFWinners.dat");
	CHAMP.open("Champions.dat");
	champDist.open("championDistribution.dat");
	CDist.open("championshipContenderDistribution.dat");
	FFDist.open("finalfourCondenterDistribution.dat");
	EEDist.open("eliteeightContenderDistribution.dat");
	// initialize random number generator, open files, and keep a counter
	for(int i =0; i < N;i++)
	{
		RoundOne(AllTeams,roundtwoTeams);
		RoundTwo(roundtwoTeams,sweetsixteenTeams);
		SweetSixteen(sweetsixteenTeams,eliteeightTeams);
		EliteEight(eliteeightTeams,finalfourTeams);
		FinalFour(finalfourTeams,championshipTeams);
		Championship(championshipTeams,WINNER);

		// Increase win count for the champion:
		WINNER[0]->AddWin();
		// Increase counts for other contenders:
		for (int j=0;j<championshipTeams.size();j++)
		{
			championshipTeams[j]->AddC();
		}
		for (int j=0;j<finalfourTeams.size();j++)
		{
			finalfourTeams[j]->AddFF();
		}
		for (int j=0;j<eliteeightTeams.size();j++)
		{
			eliteeightTeams[j]->AddEE();
		}


		// save data to a file
		for(int j=0;j<roundtwoTeams.size();j++)
		{
			ROUNDONEWINNERS << "   " << roundtwoTeams[j]->GetTeamName();
		}
		for(int j=0;j<sweetsixteenTeams.size();j++)
		{
			ROUNDTWOWINNERS << "   " << sweetsixteenTeams[j]->GetTeamName();
		}
		for(int j=0;j<eliteeightTeams.size();j++)
		{
			SSWINNERS << "   " << eliteeightTeams[j]->GetTeamName();
		}
		for(int j=0;j<finalfourTeams.size();j++)
		{
			EEWINNERS << "   " << finalfourTeams[j]->GetTeamName();
		}
		for(int j=0;j<championshipTeams.size();j++)
		{
			FFWINNERS << "   " << championshipTeams[j]->GetTeamName();
		}
		for(int j=0;j<WINNER.size();j++)
		{
			CHAMP << "   " << WINNER[j]->GetTeamName();
		}
		// start a new line in the files for the next tourny iteration
		ROUNDONEWINNERS << "\n";
		ROUNDTWOWINNERS << "\n";
		SSWINNERS << "\n";
		EEWINNERS << "\n";
		FFWINNERS << "\n";
		CHAMP << "\n";         

		roundtwoTeams.clear();
		sweetsixteenTeams.clear();
		eliteeightTeams.clear();
		finalfourTeams.clear();
		roundtwoTeams.clear();
		championshipTeams.clear();
		WINNER.clear();
		// after each tournament, the winners need to be deallocated
		count++;
		cout << count << endl;

	}

	// record number of championship wins for each team
	for (int i=0;i<AllTeams.size();i++)
	{
		champDist << AllTeams[i]->GetTeamName() << " " << AllTeams[i]->GetWin() << "\n";
		CDist << AllTeams[i]->GetTeamName() << " " << AllTeams[i]->GetC() << "\n";
		FFDist << AllTeams[i]->GetTeamName() << " " << AllTeams[i]->GetFF() << "\n";
		EEDist << AllTeams[i]->GetTeamName() << " " << AllTeams[i]->GetEE() << "\n";
	}
	// deallocate Team memory afterwards

	for (int i=0;i<AllTeams.size();i++)
	{
		delete AllTeams[i];
	}

	// close files
	ROUNDONEWINNERS.close();
	ROUNDTWOWINNERS.close();
	SSWINNERS.close();
	EEWINNERS.close();
	FFWINNERS.close();
	CHAMP.close();
	champDist.close();
	CDist.close();
	FFDist.close();
	EEDist.close();
	// end simulation
	return(0);
}

// These methods simulate each round of the tournament
void RoundOne(vector<Team*>& teams,vector<Team*>& winners)
{
	for(int i=0;i<teams.size();i=i+2)
	{
		winners.push_back(game(teams[i],teams[i+1]));
	}	
}
void RoundTwo(vector<Team*>& teams,vector<Team*>& winners)
{
	for(int i=0;i<teams.size();i=i+2)
	{
		winners.push_back(game(teams[i],teams[i+1]));
	}	
}
void SweetSixteen(vector<Team*>& teams,vector<Team*>& winners)
{
	for(int i=0;i<teams.size();i=i+2)
	{
		winners.push_back(game(teams[i],teams[i+1]));
	}	
	
}
void EliteEight(vector<Team*>& teams,vector<Team*>& winners)
{
	for(int i=0;i<teams.size();i=i+2)
	{
		winners.push_back(game(teams[i],teams[i+1]));
	}	
}
void FinalFour(vector<Team*>& teams,vector<Team*>& winners)
{
	for(int i=0;i<teams.size();i=i+2)
	{
		winners.push_back(game(teams[i],teams[i+1]));
	}	
}
void Championship(vector<Team*>& teams,vector<Team*>& winners)
{
	for(int i=0;i<teams.size();i=i+2)
	{
		winners.push_back(game(teams[i],teams[i+1]));
	}	
}

// A game simulation outputs the winner of the game
Team* game(Team* teamA, Team* teamB)
{
	double p = (double(rand()%100000))/100000.0;
	// Stat category #1:
	double n1 = teamA->GetSeed();
	double m1 = teamB->GetSeed();
	double p1 = m1/(n1+m1);
		// weight parameter
	double b1 = 0.6;
	// Stat category #2
	double ppgscore1 = (teamA -> GetPPG())/(teamA->GetOPPG());
	double ppgscore2 = (teamB -> GetPPG())/(teamB->GetOPPG());
	double p2 = ppgscore1/(ppgscore1+ppgscore2);
		// weight parameter
	double b2 = 0.35; 
	// Stat category #3
	double a1 = teamA -> GetSeasonWins();
	double a2 = teamB -> GetSeasonWins();
	double p3 = a1/(a1+a2);
		// weight parameter
	double b3 = 0.05;

	// weighted probability:
	double p0 = b1*p1 + b2*p2 + b3*p3;
	
	//cout << p1 << " " << p << endl;
	// play game
	if (p < p0)
	{
		return teamA;
	}
	else
	{
		return teamB;
	}

}