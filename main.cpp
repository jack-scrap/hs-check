#include <GL/glew.h>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"
#include "layout.h"

const unsigned int ln = 8;

int main() {
	Disp disp("Checkers", 800, 600);

	unsigned int no = ln * 2;

	Piece* team[2][no];
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < no; i++) {
			team[b][i] = new Piece(glm::vec3(i % ln, (b * 4.0) + (i / ln), 0.0) * glm::vec3(Piece::sz + (pad * 2)), b);
		}
	}

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0.0, 0.0, 0.0, 1.0);

		for (int b = 0; b < 2; b++) {
			for (int i = 0; i < no; i++) {
				team[b][i]->draw();
			}
		}

		disp.update();
	}
}
