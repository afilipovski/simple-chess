#pragma once
#include<iostream>
#include<string>
#include<cmath>
constexpr int sign_multiplier(int number) {
	if (number >= 0)
		return 1;
	else
		return -1;
}
class Chess {
public:
	friend std::ostream& print_board(std::ostream& os, const Chess& c1);
	bool possible_move(std::string from_to) {
		if (from_to.size() < 4) {
			std::cout << "Incorrect input.\n";
			return 0;
		}
		int Bx = from_to[0] - 'a';
		int By = 7 - from_to[1] + '1';
		int Dx = from_to[2] - 'a';
		int Dy = 7 - from_to[3] + '1';
		bool black_turn = round_no % 2;
		if (Bx < 0 || Bx >  7 || By < 0 || By > 7 || Dx < 0 || Dx > 7 || Dy < 0 || Dy > 7 || (Bx == Dx && By == Dy)) {
			std::cout << "Fundamental rule broken.\n";
			return 0;
		}
		if (isalpha(table[By][Bx]) && isalpha(table[Dy][Dx]) && isupper(table[By][Bx]) == isupper(table[Dy][Dx])) {
			std::cout << "Occupied by own figure.\n";
			return 0;
		}
		switch (table[By][Bx]) {
		case 'R':
		case 'r':
			if (!(Bx == Dx || By == Dy)) {
				std::cout << "Rook rule broken.\n";
				return 0;
			}
			//rook path clearance check, generates a warning that the program might go out of bounds but that is an already rectified issue
			//same goes for the bishop check
			if (Bx == Dx)
				for (int i = By + sign_multiplier(Dy-By); i != Dy; i += sign_multiplier(Dy - By))
					if (table[i][Bx] != '-') {
						std::cout << "Rook's path is obstructed.\n";
						return 0;
					}
			if (By == Dy)
				for (int i = Bx + sign_multiplier(Dx - Bx); i != Dx; i += sign_multiplier(Dx - Bx))
					if (table[By][i] != '-') {
						std::cout << "Rook's path is obstructed.\n";
						return 0;
					}
			break;
		case 'N':
		case 'n':
			//The knight "jumps over" to the destination, therefore no further movement restrictions are needed
			if (!((abs(By - Dy) == 2 && abs(Bx - Dx) == 1) || (abs(Bx - Dx) == 2 && abs(By - Dy) == 1))) {
				std::cout << "Knight rule broken.\n";
				return 0;
			}
			break;
		case 'B': 
		case 'b':
			if (!(Bx - Dx != 0 && abs(Bx - Dx) == abs(By - Dy))) {
				std::cout << "Bishop rule broken.\n";
				return 0;
			}
			{
				int i = Bx + sign_multiplier(Dx - Bx);
				int j = By + sign_multiplier(Dy - By);
				while (i != Dx) {
					if (table[j][i] != '-') {
						std::cout << "Bishop's path is obstructed.\n";
						return 0;
					}
					i += sign_multiplier(Dx - Bx); j += sign_multiplier(Dy - By);
				}
			}
			break;
		case 'Q':
		case 'q':
			if (!(Bx == Dx || By == Dy || abs(Bx - Dx) == abs(By - Dy))) {
				std::cout << "Queen rule broken.\n";
				return 0;
			}
			if (Bx == Dx) {
				for (int i = By + sign_multiplier(Dy - By); i != Dy; i += sign_multiplier(Dy - By))
					if (table[i][Bx] != '-') {
						std::cout << "Queen-Rook's path is obstructed.\n";
						return 0;
					}
			}
			else if (By == Dy) {
				for (int i = Bx + sign_multiplier(Dx - Bx); i != Dx; i += sign_multiplier(Dx - Bx))
					if (table[By][i] != '-') {
						std::cout << "Queen-Rook's path is obstructed.\n";
						return 0;
					}
			}
			else {
				int i = Bx + sign_multiplier(Dx - Bx);
				int j = By + sign_multiplier(Dy - By);
				while (i != Dx) {
					if (table[j][i] != '-') {
						std::cout << "Queen-Bishop's path is obstructed.\n";
						return 0;
					}
					i += sign_multiplier(Dx - Bx); j += sign_multiplier(Dy - By);
				}
			}
			break;
		case 'K':
		case 'k':
			if (!(abs(Bx - Dx) < 2 && abs(By - Dy) < 2)) {
				std::cout << "King rule broken.\n";
				return 0;
			}
			break;
		case 'P':
			if (!(Bx == Dx && table[Dy][Dx] == '-' && (Dy - By == -1 || Dy - By == -2 && table[Dy - 1][Dx] == '-' && By == 6) || 
				(abs(Dx - Bx) == 1 && Dy - By == -1 && islower(table[Dy][Dx])))) {
				std::cout << "White pawn rule broken or path obstructed.\n";
				return 0;
			}
			break;
		case 'p':
			if (!(Bx == Dx && table[Dy][Dx] == '-' && (Dy - By == 1 || Dy - By == 2 && table[Dy - 1][Dx] == '-' && By == 1) ||
				(abs(Dx - Bx) == 1 && Dy - By == -1 && isupper(table[Dy][Dx])))) {
				std::cout << "Black pawn rule broken or path obstructed.\n";
				return 0;
			}
			break;
		default:
			std::cout << "No figure found.\n";
			return 0;
		}
		return 1;
	}
	void move_order(std::string from_to) {
		int Bx = from_to[0] - 'a';
		int By = 7 - from_to[1] + '1';
		int Dx = from_to[2] - 'a';
		int Dy = 7 - from_to[3] + '1';
		table[Dy][Dx] = table[By][Bx];
		table[By][Bx] = '-';
		++round_no;
	}
private:
	char table[8][8] = { {'r','n','b','q','k','b','n','r'},
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