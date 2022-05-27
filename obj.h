#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "prog.h"
#include "scn.h"

class Obj {
	private:
		unsigned int _noEl;

		glm::mat4 _model = glm::mat4(1.0);

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
		Obj(GLfloat* vtc, GLushort* idc, unsigned int noEl, glm::vec3 loc, glm::vec3 rot, std::string vtx, std::string frag);

		void draw();
};
