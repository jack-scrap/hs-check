#include <GL/glew.h>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"

int main() {
	Disp disp("Checkers", 800, 600);

	Piece* team[8];
	const float sz = 2.0;
	for (int i = 0; i < sizeof team / sizeof *team; i++) {
		team[i] = new Piece(glm::vec3(i % 4, i / 4, 0.0) * glm::vec3(sz));
	}

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0.0, 0.0, 0.0, 1.0);

		for (int i = 0; i < sizeof team / sizeof *team; i++) {
			team[i]->draw();
		}

		disp.update();
	}
}
