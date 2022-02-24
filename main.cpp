#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"

int main() {
	Disp disp("Checkers", 800, 600);

	// data
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// position
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	const float rot = M_PI * 2;

	const unsigned int n = 6;

	float stride = rot / n;

	GLfloat vtc[(n * 3) + 3];
	for (int i = 0; i < n; i++) {
		vtc[(i * 3)] = sin(i * stride);
		vtc[(i * 3) + 1] = cos(i * stride);
		vtc[(i * 3) + 2] = 0.0;
	}

	vtc[n * 3] = 0.0;
	vtc[(n * 3) + 1] = 0.0;
	vtc[(n * 3) + 2] = 0.0;

	glBufferData(GL_ARRAY_BUFFER, sizeof vtc, vtc, GL_STATIC_DRAW);

	// index
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLuint idc[n * 3] = {
		0, 1, n,
		1, 2, n,
		2, 3, n,
		3, 4, n,
		4, 5, n,
		5, 0, n
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idc, idc, GL_STATIC_DRAW);

	// matrix
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 proj = glm::perspective(glm::radians(45.0), 800.0 / 600.0, 0.1, 100.0);

	// shader
	Prog prog("obj", "solid");

	/// attribute
	GLint attrPos = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPos);

	/// uniform
	GLint uniModel = glGetUniformLocation(prog._id, "model");
	GLint uniView = glGetUniformLocation(prog._id, "view");
	GLint uniProj = glGetUniformLocation(prog._id, "proj");

	// initialize
	prog.use();

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0, 0, 0, 1);

		glDrawElements(GL_TRIANGLES, sizeof idc / sizeof *idc, GL_UNSIGNED_INT, (GLvoid*) 0);

		disp.update();
	}
}
