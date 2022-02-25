#version 400

vec3[2] grey = vec3[2](
	vec3(34, 34, 34),
	vec3(102, 102, 102)
);

void main() {
	gl_FragColor = vec4(grey[0] / 225.0, 1.0);
}
