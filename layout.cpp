#include "layout.h"

float layout::stride(float el) {
	return el + (pad * 2);
}

float layout::center(float sz) {
	return sz / 2;
}
