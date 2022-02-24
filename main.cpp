#include <GL/glew.h>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"

const unsigned int ln = 8;

const float pad = 0.16;

int main() {
	Disp disp("Checkers", 800, 600);

	Piece* team[ln * 2];
	for (int i = 0; i < sizeof team / sizeof *team; i++) {
		team[i] = new Piece(glm::vec3(i % ln, i / ln, 0.0) * glm::vec3(Piece::sz + (pad * 2)), false);
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
