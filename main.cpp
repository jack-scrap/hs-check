#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "piece.h"
#include "layout.h"

class Obj {
	private:
		unsigned int _noEl;

		glm::mat4 _model = glm::mat4(1.0);
		glm::mat4 _view = glm::lookAt(glm::vec3(20.0, 20.0, 20.0), glm::vec3(0.0), glm::vec3(0, 1, 0));
		glm::mat4 _proj = glm::perspective(glm::radians(45.0), 800.0 / 600.0, 0.1, 10000.0);

		GLuint _id[3];

		GLint _attr[1];

		GLint _uni[4];

		Prog _prog;

		enum id {
			VAO,

			VBO,

			IBO
		};

		enum attr {
			POS
		};

		enum uni {
			MODEL,
			VIEW,
			PROJ,

			ACTIVE
		};

	public:
		Obj(GLfloat* vtc, GLushort* idc, unsigned int noEl, glm::vec3 loc) :
			_prog("obj", "white"),
			_noEl(noEl) {
				// data
				glGenVertexArrays(1, &_id[VAO]);
				glBindVertexArray(_id[VAO]);

				// position
				glGenBuffers(1, &_id[VBO]);
				glBindBuffer(GL_ARRAY_BUFFER, _id[VBO]);
				glBufferData(GL_ARRAY_BUFFER, _noEl * 3 * sizeof (GLfloat), vtc, GL_STATIC_DRAW);

				// matrix
				_model = glm::translate(_model, loc);

				// index
				glGenBuffers(1, &_id[IBO]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id[IBO]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _noEl * sizeof (GLushort), idc, GL_STATIC_DRAW);

				// attribute
				_attr[POS] = glGetAttribLocation(_prog._id, "pos");
				glVertexAttribPointer(_attr[POS], 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
				glEnableVertexAttribArray(_attr[POS]);

				// uniform
				_uni[MODEL] = glGetUniformLocation(_prog._id, "model");
				_uni[VIEW] = glGetUniformLocation(_prog._id, "view");
				_uni[PROJ] = glGetUniformLocation(_prog._id, "proj");
				_uni[ACTIVE] = glGetUniformLocation(_prog._id, "active");

				// initialize
				_prog.use();

				glUniformMatrix4fv(_uni[MODEL], 1, GL_FALSE, glm::value_ptr(_model));
				glUniformMatrix4fv(_uni[VIEW], 1, GL_FALSE, glm::value_ptr(_view));
				glUniformMatrix4fv(_uni[PROJ], 1, GL_FALSE, glm::value_ptr(_proj));

				_prog.unUse();
			}

		void draw() {
			glBindVertexArray(_id[VAO]);
			_prog.use();

			glDrawElements(GL_TRIANGLES, _noEl, GL_UNSIGNED_SHORT, (GLvoid*) 0);

			_prog.unUse();
			glBindVertexArray(0);
		}
};

const unsigned int ln = 8;

int main() {
	Disp disp("Checkers", 800, 600);

	unsigned int no = ln * 2;

	GLfloat vtc[2 * 2 * 3];
	int i = 0;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			vtc[i] = x;
			vtc[i + 1] = y;
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
			team[b][i] = new Piece(glm::vec3(i % ln, (b * 4.0) + (i / ln), 0.0) * glm::vec3(stride(Piece::sz), stride(Piece::sz), 0.0), b);
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
