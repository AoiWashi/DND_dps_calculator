#include "addition.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void SayHello() {
	cout << HELLO_MESSAGE << endl;
}

double f_Adv(int x, int y) {
	y++;
	double chance = 1 - ((x * 0.05) * (x * 0.05));
	return chance;
}
double f_Dis(int x, int y) {
	x++;
	double chance = (y * 0.05) * (y * 0.05);
	return chance;
}
double f_Stn(int x, int y) {
	y++;
	double chance = 1 - (x * 0.05);
	return chance;
}
double f_Elv(int x, int y) {
	y++;
	double chance = 1 - ((x * 0.05) * (x * 0.05) * (x * 0.05));
	return chance;
}