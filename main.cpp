#include"Chess.h"
int main() {
	Chess c1;
	std::string movement;
	do {
		print_board(std::cout, c1) << std::endl;
		std::cin >> movement;
	} while (c1.move(movement));
}