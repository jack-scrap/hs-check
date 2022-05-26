#version 400

in vec3 _pos;

vec3 sun = vec3(1.0, 0.0, -1.0);

vec3[2] purple = vec3[2](
	vec3(69, 59, 87),
	vec3(97, 82, 134)
);

void main() {
	vec3 normFace = normalize(cross(dFdx(_pos), dFdy(_pos)));

	float diff = max(dot(normFace, normalize(sun)), 0.0) * 0.2;

	gl_FragColor = vec4((1.0 - diff) * (purple[int(true)] / 255.0), 1.0);
}
