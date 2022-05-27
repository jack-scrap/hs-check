#include <glm/gtc/type_ptr.hpp>

#include "obj.h"

extern glm::mat4 view;
extern glm::mat4 proj;

Obj::Obj(GLfloat* vtc, GLushort* idc, unsigned int noEl, glm::vec3 loc, glm::vec3 rot, std::string vtx, std::string frag) :
	_prog(vtx, frag),
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

		for (int a = 0; a < 3; a++) {
			glm::vec3 vec = glm::vec3(0);
			vec[a] = 1;

			_model = glm::rotate(_model, rot[a], vec);
		}

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
		glUniformMatrix4fv(_uni[VIEW], 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(_uni[PROJ], 1, GL_FALSE, glm::value_ptr(proj));

		_prog.unUse();
	}

void Obj::draw() {
	glBindVertexArray(_id[VAO]);
	_prog.use();

	glUniformMatrix4fv(_uni[VIEW], 1, GL_FALSE, glm::value_ptr(view));

	glDrawElements(GL_TRIANGLES, _noEl, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	_prog.unUse();
	glBindVertexArray(0);
}
