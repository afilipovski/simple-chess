#include"Chess.h"
int main() {
	Chess c1;
	std::string movement;
	print_board(std::cout, c1) << std::endl;
	while (std::cin >> movement) {
		if (c1.possible_move(movement))
			c1.move_order(movement);
		print_board(std::cout, c1) << std::endl;
	};
}