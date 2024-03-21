#version 330 core
out vec4 FragColor;

in vec3 vertexColor; // Received from vertex shader

void main() {
    FragColor = vec4(vertexColor, 1.0); // Use the vertex color directly
}
