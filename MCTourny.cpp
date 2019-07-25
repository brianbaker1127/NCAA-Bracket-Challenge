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
#include <string>
#include <sstream>

using namespace std;



void tournamentRound(vector<Team*>&,vector<Team*>&);
Team* game(Team*,Team*);
double b1,b2,b3;

int main()
{
	int N;
	cout << "Choose the number of tournaments: " << endl;
	cin >> N;

	cout << "Enter weights for seed,win percentage, and ppg respectively:" << endl;
	cin >> b1,b2,b3;

	if (b1 + b2 + b3 != 1) 
		{
			cout << "ERROR: weights must sum to 1" << endl;
			return(0);
		}

	// allocate space to store teams and team winners
	vector<Team*> AllTeams;
	vector<Team*> roundtwoTeams;
	vector<Team*> sweetsixteenTeams;
	vector<Team*> eliteeightTeams;
	vector<Team*> finalfourTeams;
	vector<Team*> championshipTeams;
	vector<Team*> WINNER;

	// Load all team data (order: South - West - East - MidWest) //
	ifstream team_data("h.csv");

	if (!team_data.is_open()) cout << "ERROR: File Open" << endl;

	string teamname;
	string winpercentage;
	string seed;
	string ppg;
	string oppg;

	while (team_data.good())
	{
		getline(team_data,teamname,',');
		getline(team_data,winpercentage,',');
		getline(team_data,seed,',');
		getline(team_data,ppg,',');
		getline(team_data,oppg,'\n');
		stringstream w(winpercentage);
		stringstream s(seed);
		stringstream p(ppg);
		stringstream o(oppg);
		double winpercentage, ppg, oppg;
		int seed;
		w >> winpercentage;
		s >> seed;
		p >> ppg;
		o >> oppg;

		AllTeams.push_back(new Team(teamname,winpercentage,seed,ppg,oppg));
	}

	team_data.close();

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
		// simulate the six tournament rounds (1st & 2nd, sweet16, elite8, final4, championship)
		tournamentRound(AllTeams,roundtwoTeams);
		tournamentRound(roundtwoTeams,sweetsixteenTeams);
		tournamentRound(sweetsixteenTeams,eliteeightTeams);
		tournamentRound(eliteeightTeams,finalfourTeams);
		tournamentRound(finalfourTeams,championshipTeams);
		tournamentRound(championshipTeams,WINNER);

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

// This method simulates a round of the tournament
void tournamentRound(vector<Team*>& teams,vector<Team*>& winners)
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

	// Stat category #2
	double ppgscore1 = (teamA -> GetPPG())/(teamA->GetOPPG());
	double ppgscore2 = (teamB -> GetPPG())/(teamB->GetOPPG());
	double p2 = ppgscore1/(ppgscore1+ppgscore2);

	// Stat category #3
	double a1 = teamA -> GetSeasonWins();
	double a2 = teamB -> GetSeasonWins();
	double p3 = a1/(a1+a2);

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
