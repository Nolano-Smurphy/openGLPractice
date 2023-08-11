#version 150 core
in vec2 position;
//in vec3 color;
in float color;
out vec3 Color;
    
void main() {
    Color = vec3(color, color, color);
    gl_Position = vec4(position, 0.0, 1.0);
    //gl_Position = vec4(position.x, (position.y * -1.0), 0.0, 1.0); This will flip the triangle upside-down.
}