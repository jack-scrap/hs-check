#pragma once

#include <GL/glew.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "prog.h"
#include "scn.h"

class Piece {
	private:
		constexpr static float _rot = M_PI * 2;

		const static unsigned int _n = 8;

		unsigned int _pos[2];

		glm::mat4 _model = glm::mat4(1.0);
		glm::mat4 _view = glm::lookAt(cam._loc, glm::vec3(0.0), glm::vec3(0, 1, 0));
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

		Piece(unsigned int* pos, glm::vec3 loc, glm::vec3 rot, bool active);

		void draw();
};
