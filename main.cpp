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
			if (c1.try_move(Bx,By,Dx,Dy))
				c1.move_order(Bx,By,Dx,Dy);
			print_board(std::cout, c1) << std::endl;
			std::cout << (c1.is_check() ? (c1.is_mate() ? "Checkmate." : "Check.") : (c1.is_mate() ? "Stalemate." : "All ok."));
		}
	};
}