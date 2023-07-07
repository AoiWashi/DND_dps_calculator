#include "addition.h"
#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>

using namespace std;

// Want an input from the user and check if it is correct, if it is return the input.
// Git repo is created
string dmg_dice_check(string qoute) {
	bool condition = 1;
	string dmg_dice;
	bool con = 1;

	while (condition) {

		if (con) {
			cout << qoute << endl;
			cin >> dmg_dice;
			con = 0;
		}
		else {
			cout << "Wrong input, re enter:" << endl;
			cin >> dmg_dice;
		}

		if (dmg_dice == "0") {
			cout << "No damage dice" << endl;
			condition = 0;
		}

		else if (dmg_dice.length() >= 3) {

			if (isdigit((int)dmg_dice[0]) && isdigit((int)dmg_dice[dmg_dice.length() - 1])) {

				for (int i = 0; i < dmg_dice.length() - 1; i++) {

					if (isdigit((int)dmg_dice[i])) {

						if (dmg_dice[i + 1] == 'd') {

							if ((dmg_dice.length() - (i + 2)) == 1) {

								if (dmg_dice[dmg_dice.length() - 1] == '4' || dmg_dice[dmg_dice.length() - 1] == '6' || dmg_dice[dmg_dice.length() - 1] == '8') {
									condition = 0;
								}
								else {
									break;
								}
							}
							else if ((dmg_dice.length() - (i + 2)) == 2) {

								if (dmg_dice[dmg_dice.length() - 2] == '1') {

									if (dmg_dice[dmg_dice.length() - 1] == '0' || dmg_dice[dmg_dice.length() - 1] == '2') {
										condition = 0;
									}
									else {
										break;
									}
								}
								else {
									break;
								}
							}
							else {
								break;
							}
						}
					}
					else {
						break;
					}
				}
			}
		}
	}
	return dmg_dice;
}

//Get checked input from dmg_dice_check function and calculate the dice value.
float damage_dice_calculate(string d_dice) {
	float damage = 0;

	if (d_dice == "0")
		return damage;

	else {
		if (d_dice[d_dice.length() - 1] == '4') {
			damage = 2.5;
		}
		else if (d_dice[d_dice.length() - 1] == '6') {
			damage = 3.5;
		}
		else if (d_dice[d_dice.length() - 1] == '8') {
			damage = 4.5;
		}
		else if (d_dice[d_dice.length() - 1] == '0') {
			damage = 5.5;
		}
		else if (d_dice[d_dice.length() - 1] == '2') {
			damage = 6.5;
		}
		damage = int(d_dice[0]) * damage;
	}
	return damage;
}

double (*ptrFunc[4])(int, int);

enum attackTypes {
	Adv,
	Dis,
	Stn,
	Elv
};

/*Get two input from the user, check if both are correct.
If they are, calculate the hit chance and return the value.*/
double hit_chance_calculate(int min_to_hit) {
	//attackTypes attack_type;
	bool retry = 0;

	if (min_to_hit != 20) {

		while (true) {

			if (!retry) {
				cout << "Minumum die to hit(minimum 2): " << endl;
				cin >> min_to_hit;
				retry = 1;
			}
			else if (min_to_hit < 2) {
				cout << "Wrong input, re enter: " << endl;
				cin >> min_to_hit;
			}
			else {
				break;
			}
		}
	}
	retry = 0;
	int inp = -1;
	while (true) {

		if (retry) {
			cout << "Wrong input, re enter: " << endl;
		}
		cout << "enter Attack type number" << endl;
		cout << "1: adv" << endl;
		cout << "2: dis" << endl;
		cout << "3: stn" << endl;
		cout << "4: elv" << endl;
		cin >> inp;
		inp--;
		cout << inp << endl;
		retry = 1;

		if (inp >= 0 || inp < 4) {
			break;
		}
	}
	if (min_to_hit > 20) {
		min_to_hit = 20;
	}
	int y = 20 - min_to_hit;
	int x = min_to_hit - 1;
	double chance = ptrFunc[inp](x, y);
	/*switch (inp) {
	case Stn:
		chance = 1 - (x * 0.05);
		break;
	case Adv:
		chance = 1 - ((x * 0.05) * (x * 0.05));
		break;
	case Dis:
		chance = (y * 0.05) * (y * 0.05);
		break;
	case Elv:
		chance = 1 - ((x * 0.05) * (x * 0.05) * (x * 0.05));
		break;
	}*/
	cout << "chance: " << chance << endl;
	return chance;
}

//get total attack count input from the user and check if it is correct, if it is return the value.
int ext_att_input_check() {
	bool condition = 1;
	bool con = 1;
	int ext_att = 0;

	while (condition) {

		if (con) {
			cout << "How many attack per turn: " << endl;
			cin >> ext_att;
			con = 0;
		}
		else {
			cout << "Wrong input, re enter: " << endl;
			cin >> ext_att;
		}
		if (ext_att >= 1) {
			condition = 0;
		}
	}
	return ext_att;
}

//Get damage modifier input from the user and check if it is correct, if it is return the value.
int att_mod_input_check() {
	bool condition = 1;
	bool con = 1;
	int att_mod = 0;

	while (condition) {
		if (con) {
			cout << "Damage modifier: " << endl;
			cin >> att_mod;
			con = 0;
		}
		else {
			cout << "Wrong input, re enter: " << endl;
		}
		if (att_mod > 0) {
			condition = 0;
		}
	}
	return att_mod;
}

double total_damage_calculation(double hit_chance, double crt_hit_chance, int damage_mod, string damage_dice, string other_dmg_dice, string crit_dmg_bonus, string crit_dmg_only, int extra_attack) {
	double total_dmg_dice;
	double total_crit_dice;
	double normal_avg_dmg;
	double last_crit_damage;
	double last_calculated_damage;

	total_dmg_dice = damage_dice_calculate(damage_dice) + damage_dice_calculate(other_dmg_dice);
	total_crit_dice = total_dmg_dice + damage_dice_calculate(crit_dmg_bonus) + (2 * damage_dice_calculate(crit_dmg_only));
	normal_avg_dmg = (total_dmg_dice + damage_mod) * hit_chance;
	last_crit_damage = total_crit_dice * crt_hit_chance;

	last_calculated_damage = extra_attack * (normal_avg_dmg + last_crit_damage);

	return last_calculated_damage;
}


int main() {

	ptrFunc[Adv] = f_Adv;
	ptrFunc[Dis] = f_Dis;
	ptrFunc[Stn] = f_Stn;
	ptrFunc[Elv] = f_Elv;
	SayHello();
	string dmg_dice_quote = "Weapon damage dice(1d4 etc., if non enter 0): ";
	string damage_dice = dmg_dice_check(dmg_dice_quote);

	string other_dmg_dice_quote = "Other damage dice(sneak attack etc.), if non enter 0: ";
	string other_dmg_dice = dmg_dice_check(other_dmg_dice_quote);

	string crit_dmg_bonus_quote = "Crit bonus dice(half orc feat etc.), if non enter 0: ";
	string crit_dmg_bonus = dmg_dice_check(crit_dmg_bonus_quote);

	string crit_dmg_only_quote = "Damage bonus only crit(divene smite when crit etc.), if non enter 0: ";
	string crit_dmg_only = dmg_dice_check(crit_dmg_only_quote);

	double hit_chance = hit_chance_calculate(0);

	double crit_hit_chance = hit_chance_calculate(20);

	int extra_attack = ext_att_input_check();

	int damage_mod = att_mod_input_check();

	cout << "=> " << total_damage_calculation(hit_chance, crit_hit_chance, damage_mod, damage_dice, other_dmg_dice, crit_dmg_bonus, crit_dmg_only, extra_attack);

	return 0;
}