#version 400

vec3[2] grey = vec3[2](
	vec3(34, 34, 34),
	vec3(102, 102, 102)
);

vec3[2] purple = vec3[2](
	vec3(69, 59, 87),
	vec3(97, 82, 134)
);

uniform bool active;

void main() {
	gl_FragColor = vec4(purple[int(active)] / 255.0, 1.0);
}
