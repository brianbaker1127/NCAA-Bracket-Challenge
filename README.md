# NCAA-Bracket-Challenge

## Required source files: MCTourny.cpp, Team.cpp
## Required headers: Team.h
## Required .csv files: march_madness_data.csv

This repository consists of files that run a Monte Carlo simulation of a NCAA March Madness basketball tournament.

## Use:
To run, compile MCTourny.cpp and execute it. The command prompt asks for the number of tournaments to run in the simulation.
It then asks for 3 "weight parameters" that determine how important various tournament statistics play into the simulation. 
The user should enter each parameter 1 by 1 separated by a comma. The 3 weights should sum to 1. 

## Results:
Running MCTourny.cpp returns several .dat files that show all tournament winners and winner distributions. E.g. championDistribution.dat is a list of all teams that have won the tournament along with the number of times each team won.
