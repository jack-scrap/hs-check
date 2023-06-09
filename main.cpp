#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"
#include "obj.h"
#include "layout.h"
#include "cam.h"
#include "math.h"

glm::mat4 view = glm::mat4(1.0);
glm::mat4 proj = glm::mat4(1.0);

int main() {
	Disp disp("Checkers", 800, 600);

	view = glm::lookAt(cam._loc, glm::vec3(0.0), glm::vec3(0, 1, 0));
	proj = glm::perspective(glm::radians(45.0), (double) (disp._res[X] / (float) disp._res[Y]), 0.1, 10000.0);

	/* board */
	const unsigned int ln = 8;

	unsigned int no = ln * 2;

	const float dim[2] = {
		ln * layout::stride(Piece::sz),
		ln * layout::stride(Piece::sz)
	};

	GLfloat vtc[2 * 2 * 3];
	int i = 0;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			vtc[i] = x * ln * layout::stride(Piece::sz);
			vtc[i + 1] = y * ln * layout::stride(Piece::sz);
			vtc[i + 2] = 0.0;

			i += 3;
		}
	}

	GLushort idc[2 * 3] = {
		2, 1, 0,
		3, 1, 2
	};

	Obj* board = new Obj(vtc, idc, sizeof idc / sizeof *idc, glm::vec3(-layout::center(dim[X]), 0.0, -layout::center(dim[Y])), glm::vec3(M_PI / 2, 0.0, 0.0), "obj", "board");

	/* pieces */
	Piece* team[2][no];
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < no; i++) {
			unsigned int pos[2] = {
				0
			};

			team[b][i] = new Piece(pos, glm::vec3(layout::center(Piece::sz), layout::center(Piece::sz), 0.0) + glm::vec3(i % ln, (b * ln) + (i / ln), 0.0) * glm::vec3(layout::stride(Piece::sz), layout::stride(Piece::sz), 0.0), glm::vec3(M_PI / 2, 0.0, 0.0), b);
		}
	}

	bool camView = false;

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_F5:
						camView = !camView;

						if (camView) {
							cam._loc = glm::vec3(-30.0, 30.0, -30.0);

							proj = glm::perspective(glm::radians(45.0), (double) (disp._res[X] / (float) disp._res[Y]), 0.1, 10000.0);
						} else {
							cam._loc = glm::vec3(-(dim[X] / 2), 30.0, -(dim[Y] / 2));

							proj = glm::ortho(-(disp._res[X] / 2.0), disp._res[X] / 2.0, -(disp._res[Y] / 2.0), disp._res[Y] / 2.0, 0.1, 10000.0);
						}

						view = glm::lookAt(cam._loc, glm::vec3(0.0), glm::vec3(0, 1, 0));

						board->_prog.use();

						glUniformMatrix4fv(board->_uni[Obj::VIEW], 1, GL_FALSE, glm::value_ptr(view));
						glUniformMatrix4fv(board->_uni[Obj::PROJ], 1, GL_FALSE, glm::value_ptr(proj));

						board->_prog.unUse();

						for (int b = 0; b < 2; b++) {
							for (int i = 0; i < no; i++) {
								team[b][i]->_prog.use();

								glUniformMatrix4fv(team[b][i]->_uni[Obj::VIEW], 1, GL_FALSE, glm::value_ptr(view));
								glUniformMatrix4fv(team[b][i]->_uni[Obj::PROJ], 1, GL_FALSE, glm::value_ptr(proj));

								team[b][i]->_prog.unUse();
							}
						}

						break;
				}
			}

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
