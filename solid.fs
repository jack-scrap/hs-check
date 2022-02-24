#version 400

vec3 inert = vec3(69, 59, 87);
vec3 active = vec3(97, 82, 134);

void main() {
	gl_FragColor = vec4(active / 255.0, 1.0);
}
