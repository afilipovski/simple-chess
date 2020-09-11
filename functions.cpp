#include<iostream>
#include"Chess.h"
std::ostream& print_board(std::ostream& os, const Chess& c1) {
	std::cout << "  | A B C D E F G H\n-------------------\n";
	for (int i = 0; i < 8; i++) {
		std::cout << i << " | ";
		for (int j = 0; j < 8; j++) {
			os << c1.table[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}