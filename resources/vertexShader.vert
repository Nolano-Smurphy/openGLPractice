#version 150 core
in vec2 position;
in float color;
out vec3 Color;
    
void main() {
    Color = vec3(color, color, color);
    gl_Position = vec4(position, 0.0, 1.0);
}