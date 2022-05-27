#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"
#include "obj.h"
#include "layout.h"
#include "cam.h"

glm::mat4 view = glm::mat4(1.0);
glm::mat4 proj = glm::mat4(1.0);

int main() {
	Disp disp("Checkers", 800, 600);

	view = glm::lookAt(cam._loc, glm::vec3(0.0), glm::vec3(0, 1, 0));
	proj = glm::perspective(glm::radians(45.0), 800.0 / 600.0, 0.1, 10000.0);

	/* board */
	const unsigned int ln = 8;

	unsigned int no = ln * 2;

	const float dim[2] = {
		ln * stride(Piece::sz),
		ln * stride(Piece::sz)
	};

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

	GLushort idc[2 * 3];
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < 3; i++) {
			idc[b ? ((2 * 3) - 1) - i : i] = b ? ((2 * 2) - 1) - i : i;
		}
	}

	Obj* board = new Obj(vtc, idc, sizeof idc / sizeof *idc, glm::vec3(0.0), glm::vec3(M_PI / 2, 0.0, 0.0), "obj", "board");

	/* pieces */
	Piece* team[2][no];
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < no; i++) {
			unsigned int pos[2] = {
				0
			};

			team[b][i] = new Piece(pos, glm::vec3(Piece::sz / 2, Piece::sz / 2, 0.0) + glm::vec3(i % ln, (b * ln) + (i / ln), 0.0) * glm::vec3(stride(Piece::sz), stride(Piece::sz), 0.0), glm::vec3(M_PI / 2, 0.0, 0.0), b);
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
							cam._loc = glm::vec3(30.0, 30.0, 30.0);
						} else {
							cam._loc = glm::vec3(-(dim[0] / 2), 30.0, -(dim[1] / 2));
						}

						view = glm::lookAt(cam._loc, glm::vec3(0.0), glm::vec3(0, 1, 0));

						board->_prog.use();

						glUniformMatrix4fv(board->_uni[Obj::VIEW], 1, GL_FALSE, glm::value_ptr(view));

						board->_prog.unUse();

						for (int b = 0; b < 2; b++) {
							for (int i = 0; i < no; i++) {
								team[b][i]->_prog.use();

								glUniformMatrix4fv(team[b][i]->_uni[Obj::VIEW], 1, GL_FALSE, glm::value_ptr(view));

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
