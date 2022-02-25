#include <glm/gtc/type_ptr.hpp>

#include "piece.h"

Piece::Piece(glm::vec3 loc, bool active) :
	_prog("obj", "solid") {
		// data
		glGenVertexArrays(1, &_id[VAO]);
		glBindVertexArray(_id[VAO]);

		// position
		glGenBuffers(1, &_id[VBO]);
		glBindBuffer(GL_ARRAY_BUFFER, _id[VBO]);

		float stride = _rot / _n;

		int teamSz = 8 * 3;
		for (int b = 0; b < 2; b++) {
			for (int i = 0; i < _n; i++) {
				_vtc[(b * teamSz) + (i * 3)] = sin(i * stride);
				_vtc[(b * teamSz) + (i * 3) + 1] = cos(i * stride);
				_vtc[(b * teamSz) + (i * 3) + 2] = b * 0.2;
			}
		}

		_vtc[_n * 2 * 3] = 0.0;
		_vtc[(_n * 2 * 3) + 1] = 0.0;
		_vtc[(_n * 2 * 3) + 2] = 0.0;

		glBufferData(GL_ARRAY_BUFFER, sizeof _vtc, _vtc, GL_STATIC_DRAW);

		// matrix
		_model = glm::translate(_model, loc);

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
		_uni[ACTIVE] = glGetUniformLocation(_prog._id, "b");

		// initialize
		_prog.use();

		glUniformMatrix4fv(_uni[MODEL], 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(_uni[VIEW], 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(_uni[PROJ], 1, GL_FALSE, glm::value_ptr(_proj));
		glUniform1i(_uni[ACTIVE], active);

		_prog.unUse();
	}

void Piece::draw() {
	glBindVertexArray(_id[VAO]);
	_prog.use();

	glDrawElements(GL_TRIANGLES, sizeof _idc / sizeof *_idc, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	_prog.unUse();
	glBindVertexArray(0);
}
