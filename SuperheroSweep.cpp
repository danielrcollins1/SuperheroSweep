/*
	Name: Superhero Sweep
	Copyright: 2010
	Author: Daniel R. Collins
	Date: 05/05/21 22:24
	Description: Assess Superhero sweep kill variation
		by Monte Carlo method.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

/***********************************************/
// Global constants

// Fighter level (i.e., number of sweep attacks)
const int FIGHTER_LEVEL = 12;

// Chance to hit: 95% true for level 8 vs. AC 7,
//   or level 12+ vs. any AC 2-9.
const float HIT_PERCENT = 95;

// Damage die: sword, axe, polearm: 1d8.
const int DAMAGE_DIE = 8;

// Damage bonus: +2 Strength and +2 magic.
const int DAMAGE_BONUS = 4;

// Enemy hit dice
const int ENEMY_HIT_SIDES = 6;
const int ENEMY_HIT_DICE = 1;

// Rounds per turn
const int ROUNDS_PER_TURN = 3;

// Number of simulated turns
const int NUM_TRIALS = 10000;

/***********************************************/
// Functions

// Roll hit points for one target
int newTargetHitPoints () {
	int sum = 0;
	for (int i = 0; i < ENEMY_HIT_DICE; i++) {
		sum += rand() % ENEMY_HIT_SIDES + 1;
	}
	return sum;
}

// Roll damage for one attack
int rollDamage () {
	return rand() % DAMAGE_DIE + DAMAGE_BONUS + 1;
}

// Simulate one turn of combat
//   Return number of individual kills
int runOneTurn () {
	int kills = 0;
	int targetHp = newTargetHitPoints();
	int attacksPerTurn = FIGHTER_LEVEL * ROUNDS_PER_TURN;
	for (int i = 0; i < attacksPerTurn; i++) {
		if (rand() % 100 < HIT_PERCENT) {
			targetHp -= rollDamage();
			if (targetHp <= 0) {
				kills++;
				targetHp = newTargetHitPoints();
			}
		}
	}
	return kills;
}

// Convert individual kills to figures
//   Assumes 1:10 scale
int convertKillsToFigs (int kills) {
	return (kills + 5) / 10;
}

// Run all trials; tally fig-kills made
void runAllTrials () {

	// Run trials
	const int MAX_FIG_KILLS = 10;
	int figKillsInTurn[MAX_FIG_KILLS] = {0};
	for (int i = 0; i < NUM_TRIALS; i++) {
		int kills = runOneTurn();
		int figKills = convertKillsToFigs(kills);
		if (figKills < MAX_FIG_KILLS) {
			figKillsInTurn[figKills]++;	
		}
	}
	
	// Print results
	cout << setw(10) << "Fig Kills" << setw(10) << "Frequency" << endl;
	for (int i = 0; i < MAX_FIG_KILLS; i++) {
		cout << setw(10) << i << setw(10) << figKillsInTurn[i] << endl;	
	}
	cout << endl;
}

// Print program banner
void printBanner () {
	cout << "Superhero Sweep Simulator\n";
	cout << "-------------------------\n";
	cout << "Fighter Level: " << FIGHTER_LEVEL << endl;
	cout << endl;
}

// Main test driver.
int main(int argc, char** argv) {
	srand(time(0));
	printBanner();
	runAllTrials();
	return 0;
}
