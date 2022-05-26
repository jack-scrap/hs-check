#version 400

in vec3 _pos;

const float pad = 0.16;
const float sz = 2.0;

const float stride = sz + (pad * 2);

vec3[2] grey = vec3[2](
	vec3(34, 34, 34),
	vec3(102, 102, 102)
);

void main() {
	gl_FragColor = vec4(grey[int(mod(_pos.x, stride * 2) > stride ^^ mod(_pos.y, stride * 2) > stride)] / 225.0, 1.0);
}
