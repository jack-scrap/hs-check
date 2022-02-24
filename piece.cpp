#include <glm/gtc/type_ptr.hpp>

#include "piece.h"

Piece::Piece() :
	_prog("obj", "solid") {
		// data
		glGenVertexArrays(1, &_id[VAO]);
		glBindVertexArray(_id[VAO]);

		// position
		glGenBuffers(1, &_id[VBO]);
		glBindBuffer(GL_ARRAY_BUFFER, _id[VBO]);

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
		glGenBuffers(1, &_id[IBO]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id[IBO]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof _idc, _idc, GL_STATIC_DRAW);

		// attribute
		_attr[POS] = glGetAttribLocation(_prog._id, "pos");
		glVertexAttribPointer(_attr[POS], 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
		glEnableVertexAttribArray(_attr[POS]);

		// uniform
		_uni[MODEL] = glGetUniformLocation(_prog._id, "model");
		_uni[VIEW] = glGetUniformLocation(_prog._id, "view");
		_uni[PROJ] = glGetUniformLocation(_prog._id, "proj");

		// initialize
		_prog.use();

		glUniformMatrix4fv(_uni[MODEL], 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(_uni[VIEW], 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(_uni[PROJ], 1, GL_FALSE, glm::value_ptr(_proj));

		_prog.unUse();
	}

void Piece::draw() {
	glBindVertexArray(_id[VAO]);
	_prog.use();

	glDrawElements(GL_TRIANGLES, sizeof _idc / sizeof *_idc, GL_UNSIGNED_INT, (GLvoid*) 0);

	_prog.unUse();
	glBindVertexArray(0);
}