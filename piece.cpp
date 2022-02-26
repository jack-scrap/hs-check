#include <glm/gtc/type_ptr.hpp>

#include "piece.h"

Piece::Piece(unsigned int* pos, glm::vec3 loc, glm::vec3 rot, bool active) :
	_prog("obj", "solid") {
		for (int i = 0; i < 2; i++) {
			_pos[i] = pos[i];
		}

		// data
		glGenVertexArrays(1, &_id[VAO]);
		glBindVertexArray(_id[VAO]);

		// position
		glGenBuffers(1, &_id[VBO]);
		glBindBuffer(GL_ARRAY_BUFFER, _id[VBO]);

		float stride = _rot / _n;

		GLfloat vtc[((8 * 3) * 2) + 3];

		int teamSz = 8 * 3;
		for (int b = 0; b < 2; b++) {
			for (int i = 0; i < _n; i++) {
				vtc[(b * teamSz) + (i * 3)] = sin(i * stride);
				vtc[(b * teamSz) + (i * 3) + 1] = cos(i * stride);
				vtc[(b * teamSz) + (i * 3) + 2] = b * 0.2;
			}
		}

		vtc[_n * 2 * 3] = 0.0;
		vtc[(_n * 2 * 3) + 1] = 0.0;
		vtc[(_n * 2 * 3) + 2] = 0.0;

		glBufferData(GL_ARRAY_BUFFER, sizeof vtc, vtc, GL_STATIC_DRAW);

		GLushort idc[8 * 3 * 2] = {
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idc, idc, GL_STATIC_DRAW);

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

	glDrawElements(GL_TRIANGLES, _n * 3 * 2, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	_prog.unUse();
	glBindVertexArray(0);
}
