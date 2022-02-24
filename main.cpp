#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"

const float rot = M_PI * 2;

class Piece {
	private:
		const unsigned int _n = 6;

		GLfloat _vtc[(6 * 3) + 3];

		GLuint _idc[6 * 3] = {
			0, 1, _n,
			1, 2, _n,
			2, 3, _n,
			3, 4, _n,
			4, 5, _n,
			5, 0, _n
		};

		glm::mat4 _model = glm::mat4(1.0);
		glm::mat4 _view = glm::lookAt(glm::vec3(3.0, 3.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
		glm::mat4 _proj = glm::perspective(glm::radians(45.0), 800.0 / 600.0, 0.1, 100.0);

		GLuint _vao;
		GLuint _vbo;

		GLuint _ibo;

		Prog _prog;

	public:
		Piece() :
			_prog("obj", "solid") {
				// data
				glGenVertexArrays(1, &_vao);
				glBindVertexArray(_vao);

				// position
				glGenBuffers(1, &_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, _vbo);

				float stride = rot / _n;

				for (int i = 0; i < _n; i++) {
					_vtc[(i * 3)] = sin(i * stride);
					_vtc[(i * 3) + 1] = cos(i * stride);
					_vtc[(i * 3) + 2] = 0.0;
				}

				_vtc[_n * 3] = 0.0;
				_vtc[(_n * 3) + 1] = 0.0;
				_vtc[(_n * 3) + 2] = 0.0;

				glBufferData(GL_ARRAY_BUFFER, sizeof _vtc, _vtc, GL_STATIC_DRAW);

				// index
				glGenBuffers(1, &_ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof _idc, _idc, GL_STATIC_DRAW);

				/// attribute
				GLint attrPos = glGetAttribLocation(_prog._id, "pos");
				glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
				glEnableVertexAttribArray(attrPos);

				/// uniform
				GLint uniModel = glGetUniformLocation(_prog._id, "model");
				GLint uniView = glGetUniformLocation(_prog._id, "view");
				GLint uniProj = glGetUniformLocation(_prog._id, "proj");

				// initialize
				_prog.use();

				glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(_model));
				glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(_view));
				glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(_proj));
			}

		void draw() {
			glBindVertexArray(_vao);
			_prog.use();

			glDrawElements(GL_TRIANGLES, sizeof _idc / sizeof *_idc, GL_UNSIGNED_INT, (GLvoid*) 0);

			_prog.unUse();
			glBindVertexArray(0);

		}
};

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
