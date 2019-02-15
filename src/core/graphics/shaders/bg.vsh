// #version 130

uniform float t;
uniform vec4 position;

void main(void) {
    gl_Position = position;
    gl_PointSize = 10.0;
}
