#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "prog.h"

class Piece {
	private:
		const float _rot = M_PI * 2;

		const static unsigned int _n = 8;

		GLfloat _vtc[((8 * 3) * 2) + 3];

		GLushort _idc[8 * 3 * 2] = {
			0, 1, _n,
			1, 2, _n,
			2, 3, _n,
			3, 4, _n,
			4, 5, _n,
			5, 6, _n,
			6, 7, _n,
			7, 8, _n,

			8, 9, _n,
			9, 10, _n,
			10, 11, _n,
			11, 12, _n,
			12, 13, _n,
			13, 14, _n,
			14, 15, _n,
			15, 0, _n
		};

		glm::mat4 _model = glm::mat4(1.0);
		glm::mat4 _view = glm::lookAt(glm::vec3(30.0, 30.0, 30.0), glm::vec3(0.0), glm::vec3(0, 1, 0));
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
		constexpr static float sz = 2.0;

		Piece(glm::vec3 loc, glm::vec3 rot, bool active);

		void draw();
};
