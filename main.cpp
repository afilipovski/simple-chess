#include"Chess.h"
int main() {
	Chess c1;
	std::string movement;
	print_board(std::cout, c1) << std::endl;
	while (std::cin >> movement) {
		if (movement.size() < 4) {
			std::cout << "Invalid input, try again. ";
		}
		else {
			int Bx = movement[0] - 'a';
			int By = 7 - movement[1] + '1';
			int Dx = movement[2] - 'a';
			int Dy = 7 - movement[3] + '1';
			if (c1.possible_move(Bx,By,Dx,Dy,1))
				c1.move_order(Bx,By,Dx,Dy);
			print_board(std::cout, c1) << std::endl;
		}
	};
}