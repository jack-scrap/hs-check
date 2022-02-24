#version 400

vec3[2] purple = vec3[2](
	vec3(69, 59, 87),
	vec3(97, 82, 134)
);

void main() {
	gl_FragColor = vec4(purple[1] / 255.0, 1.0);
}
