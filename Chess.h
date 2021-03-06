#pragma once
#include<iostream>
#include<string>
#include<cmath>
constexpr int sign_multiplier(int number) {
	return (number >= 0 ? 1 : -1);
}
class Chess {
public:
	friend std::ostream& print_board(std::ostream& os, const Chess& c1);
	bool try_move(int Bx, int By, int Dx, int Dy) {
		bool validity = correct_turn(Bx, By) && possible_move(Bx, By, Dx, Dy);
		if (!validity)
			return 0;
		char old_figure = table[Dy][Dx];
		table[Dy][Dx] = table[By][Bx];
		table[By][Bx] = '-';
		validity = !is_check();
		table[By][Bx] = table[Dy][Dx];
		table[Dy][Dx] = old_figure;
		return validity;
	}
	bool is_check() {
		char king_needed = (round_no % 2 ? 'k' : 'K');
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (table[i][j] == king_needed)
					return under_attack(j, i);
			}
		}
		return 0;
	}
	//checks for stalemate or checkmate - is_check()&&is_mate == checkmate >>>> !is_check()&&is_mate == stalemate
	bool is_mate() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						if (try_move(i, j, k, l))
							return 0;
					}
				}
			}
		}
		return 1;
	}
	void move_order(int Bx, int By, int Dx, int Dy) {
		table[Dy][Dx] = table[By][Bx];
		table[By][Bx] = '-';
		char choice;
		while (true) {
			if (Dy == 0 && table[Dy][Dx] == 'P' || Dy == 7 && table[Dy][Dx] == 'p') {
				std::cout << "Choose one of the following figures to which you want your pawn to be promoted: Q, R, B, N: ";
				std::cin >> choice;
				switch (choice) {
				case 'Q':
				case 'q':
				case 'R':
				case 'r':
				case 'B':
				case 'b':
				case 'N':
				case 'n':
					table[Dy][Dx] = (round_no % 2 ? tolower(choice) : toupper(choice));
					break;
				default:
					continue;
				}
			}
			break;
		}
		round_no++;
	}
private:
	bool possible_move(int Bx, int By, int Dx, int Dy) {
		if (Bx < 0 || Bx >  7 || By < 0 || By > 7 || Dx < 0 || Dx > 7 || Dy < 0 || Dy > 7 || (Bx == Dx && By == Dy))
			return 0;
		if (isalpha(table[By][Bx]) && isalpha(table[Dy][Dx]) && isupper(table[By][Bx]) == isupper(table[Dy][Dx]))
			return 0;
		switch (table[By][Bx]) {
		case 'R':
		case 'r':
			if (!(Bx == Dx || By == Dy))
				return 0;
			//rook path clearance check, generates a warning that the program might go out of the bounds of the array but that is an already rectified issue
			//same goes for the bishop check
			if (Bx == Dx)
				for (int i = By + sign_multiplier(Dy - By); i != Dy; i += sign_multiplier(Dy - By))
					if (table[i][Bx] != '-')
						return 0;
			if (By == Dy)
				for (int i = Bx + sign_multiplier(Dx - Bx); i != Dx; i += sign_multiplier(Dx - Bx))
					if (table[By][i] != '-')
						return 0;
			break;
		case 'N':
		case 'n':
			//The knight "jumps over" to the destination, therefore no further movement restrictions are needed
			if (!((abs(By - Dy) == 2 && abs(Bx - Dx) == 1) || (abs(Bx - Dx) == 2 && abs(By - Dy) == 1)))
				return 0;
			break;
		case 'B':
		case 'b':
			if (!(Bx - Dx != 0 && abs(Bx - Dx) == abs(By - Dy)))
				return 0;
			//ADDITIONAL BISHOP SCOPE
			{
				int i = Bx + sign_multiplier(Dx - Bx);
				int j = By + sign_multiplier(Dy - By);
				while (i != Dx) {
					if (table[j][i] != '-')
						return 0;
					i += sign_multiplier(Dx - Bx); j += sign_multiplier(Dy - By);
				}
			}
			break;
		case 'Q':
		case 'q':
			if (!(Bx == Dx || By == Dy || abs(Bx - Dx) == abs(By - Dy)))
				return 0;
			if (Bx == Dx) {
				for (int i = By + sign_multiplier(Dy - By); i != Dy; i += sign_multiplier(Dy - By))
					if (table[i][Bx] != '-')
						return 0;
			}
			else if (By == Dy) {
				for (int i = Bx + sign_multiplier(Dx - Bx); i != Dx; i += sign_multiplier(Dx - Bx))
					if (table[By][i] != '-')
						return 0;
			}
			else {
				int i = Bx + sign_multiplier(Dx - Bx);
				int j = By + sign_multiplier(Dy - By);
				while (i != Dx) {
					if (table[j][i] != '-')
						return 0;
					i += sign_multiplier(Dx - Bx); j += sign_multiplier(Dy - By);
				}
			}
			break;
		case 'K':
		case 'k':
			if (!(abs(Bx - Dx) < 2 && abs(By - Dy) < 2))
				return 0;
			break;
		case 'P':
			if (!(Bx == Dx && table[Dy][Dx] == '-' && (Dy - By == -1 || Dy - By == -2 && table[Dy - 1][Dx] == '-' && By == 6) ||
				(abs(Dx - Bx) == 1 && Dy - By == -1 && islower(table[Dy][Dx]))))
				return 0;
			break;
		case 'p':
			if (!(Bx == Dx && table[Dy][Dx] == '-' && (Dy - By == 1 || Dy - By == 2 && table[Dy - 1][Dx] == '-' && By == 1) ||
				(abs(Dx - Bx) == 1 && Dy - By == 1 && isupper(table[Dy][Dx]))))
				return 0;
			break;
		default:
			return 0;
		}
		return 1;
	}
	bool correct_turn(int Bx, int By) {
		return round_no % 2 == 0 && isupper(table[By][Bx]) || round_no % 2 == 1 && islower(table[By][Bx]);
		return 1;
	}
	//Checks whether a field is under attack by an enemy figure
	bool under_attack(int Bx, int By) {
		if (round_no % 2) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (isupper(table[i][j]) && possible_move(j, i, Bx, By))
						return 1;
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (islower(table[i][j]) && possible_move(j, i, Bx, By))
						return 1;
				}
			}
		}
		return 0;
	}
	char table[8][8] = { {'r','n','b','q','k','b','p','-'},
						 {'p','p','p','p','p','p','p','p'},
						 {'-','-','-','-','-','-','-','-'},
						 {'-','-','-','-','-','-','-','-'},
						 {'-','-','-','-','-','-','-','-'},
						 {'-','-','-','-','-','-','-','-'},
						 {'P','P','P','P','P','P','P','P'},
						 {'R','N','B','Q','K','B','N','R'}, };
	int round_no = 0;
};
std::ostream& print_board(std::ostream& os, const Chess& c1);
