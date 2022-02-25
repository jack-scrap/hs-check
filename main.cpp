#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"
#include "obj.h"
#include "layout.h"

int main() {
	Disp disp("Checkers", 800, 600);

	const unsigned int ln = 8;

	unsigned int no = ln * 2;

	GLfloat vtc[2 * 2 * 3];
	int i = 0;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			vtc[i] = x * ln * stride(Piece::sz);
			vtc[i + 1] = y * ln * stride(Piece::sz);
			vtc[i + 2] = 0.0;

			i += 3;
		}
	}

	GLushort idc[] = {
		0, 1, 2,
		2, 1, 3
	};

	Obj* board = new Obj(vtc, idc, sizeof idc / sizeof *idc, glm::vec3(0.0));

	Piece* team[2][no];
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < no; i++) {
			team[b][i] = new Piece(glm::vec3(Piece::sz / 2, Piece::sz / 2, 0.0) + glm::vec3(i % ln, (b * (ln / 2)) + (i / ln), 0.0) * glm::vec3(stride(Piece::sz), stride(Piece::sz), 0.0), b);
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

		board->draw();

		for (int b = 0; b < 2; b++) {
			for (int i = 0; i < no; i++) {
				team[b][i]->draw();
			}
		}

		disp.update();
	}
}
