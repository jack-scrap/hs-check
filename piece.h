#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "prog.h"

class Piece {
	private:
		const float rot = M_PI * 2;

		const static unsigned int _n = 8;

		GLfloat _vtc[(8 * 3) + 3];

		GLuint _idc[8 * 3] = {
			0, 1, _n,
			1, 2, _n,
			2, 3, _n,
			3, 4, _n,
			4, 5, _n,
			5, 6, _n,
			6, 7, _n,
			7, 0, _n
		};

		glm::mat4 _model = glm::mat4(1.0);
		glm::mat4 _view = glm::lookAt(glm::vec3(5.0, 5.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
		glm::mat4 _proj = glm::perspective(glm::radians(45.0), 800.0 / 600.0, 0.1, 100.0);

		GLuint _id[3];

		GLint _attr[1];

		GLint _uni[3];

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
			PROJ
		};

	public:
		Piece(glm::vec3 loc);

		void draw();
};
