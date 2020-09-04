#pragma once
#include<iostream>
#include<string>
#include<cmath>
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
		const char figura_tip = table[By][Bx];
		bool black_turn = round_no % 2;
		if ((!black_turn && islower(figura_tip)) || (black_turn && isupper(figura_tip))) {
			std::cerr << "Incorrect turn.\n";
			return 0;
		}
		if (Bx < 0 || Bx >  7 || By < 0 || By > 7 || Dx < 0 || Dx > 7 || Dy < 0 || Dy > 7 || (Bx == Dx && By == Dy)) {
			std::cerr << "Fundamental rule broken.\n";
			return 0;
		}
		if ((black_turn && islower(table[Dy][Dx])) || (!black_turn && isupper(table[Dy][Dx]))) {
			std::cout << "Attacking own figure.\n";
			return 0;
		}
		switch (figura_tip) {
		case 'R':
		case 'r':
			if (!((Bx == Dx) || (By == Dy))) {
				std::cout << "Rook rule broken.\n";
				return 0;
			}
			break;
		case 'N':
		case 'n':
			if (!((abs(By - Dy) == 2 && abs(Bx - Dx) == 1) || (abs(Bx - Dx) == 2 && abs(By - Dy) == 1))) {
				std::cout << "Knight rule broken.\n";
				return 0;
			}
			break;
		case 'B': 
		case 'b':
			if (!(Bx - Dx != 0 && abs(Bx - Dx) == abs(By - Dy))) {
				std::cerr << "Bishop rule broken.\n";
				return 0;
			}
			break;
		case 'Q':
		case 'q':
			if (!(((Bx == Dx) ^ (By == Dy)) || (Bx - Dx != 0 && abs(Bx - Dx) == abs(By - Dy)))) {
				std::cerr << "Queen rule broken.\n";
				return 0;
			}
			break;
		case 'K':
		case 'k':
			if (!(abs(Bx - Dx) < 2 && abs(By - Dy) < 2)) {
				std::cerr << "King rule broken.\n";
				return 0;
			}
			break;
		case 'P':
			if (!(Bx == Dx && (Dy - By == -2 && By == 6 || Dy - By == -1) || (abs(Dx-Bx)==1 && Dy-By == -1 && islower(table[Dy][Dx])))) {
				std::cout << "White pawn rule broken.\n";
				return 0;
			}
			break;
		case 'p':
			if (!(Bx == Dx && (Dy - By == 2 && By == 1 || Dy - By == 1) || (abs(Dx - Bx) == 1 && Dy - By == 1 && isupper(table[Dy][Dx])))) {
				std::cout << "Black pawn rule broken.\n";
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