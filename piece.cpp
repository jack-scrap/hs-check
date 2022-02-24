#include <glm/gtc/type_ptr.hpp>

#include "piece.h"

Piece::Piece() :
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

		// attribute
		_attrPos = glGetAttribLocation(_prog._id, "pos");
		glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
		glEnableVertexAttribArray(_attrPos);

		// uniform
		_uniModel = glGetUniformLocation(_prog._id, "model");
		_uniView = glGetUniformLocation(_prog._id, "view");
		_uniProj = glGetUniformLocation(_prog._id, "proj");

		// initialize
		_prog.use();

		glUniformMatrix4fv(_uniModel, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(_uniProj, 1, GL_FALSE, glm::value_ptr(_proj));

		_prog.unUse();
	}

void Piece::draw() {
	glBindVertexArray(_vao);
	_prog.use();

	glDrawElements(GL_TRIANGLES, sizeof _idc / sizeof *_idc, GL_UNSIGNED_INT, (GLvoid*) 0);

	_prog.unUse();
	glBindVertexArray(0);
}
