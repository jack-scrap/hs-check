#include <GL/glew.h>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"

int main() {
	Disp disp("Checkers", 800, 600);

	Piece piece;

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0, 0, 0, 1);

		piece.draw();

		disp.update();
	}
}
