const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos; // Position
layout (location = 1) in vec3 aNormal; // Normal vector

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 Normal; // Pass normal to the fragment shader
out vec3 FragPos; // Pass fragment position to the fragment shader

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Calculate normal for the fragment
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal; // Received from vertex shader
in vec3 FragPos; // Received from vertex shader

uniform vec3 lightPos; // Position of the light source in world space
uniform vec3 viewPos; // Position of the camera in world space
uniform vec3 lightColor; // Color of the light
uniform vec3 objectColor; // Color of the object

void main() {
    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine the two components
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}

)glsl";

const char* vertexShaderSourceTexture = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos; // Position
layout (location = 1) in vec3 aNormal; // Normal vector
layout (location = 2) in vec2 aTexCoords; // Texture coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal; // Pass normal to the fragment shader
out vec3 FragPos; // Pass fragment position to the fragment shader
out vec2 TexCoords; // Pass texture coordinates to the fragment shader

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Calculate normal for the fragment
    TexCoords = aTexCoords; // Pass texture coordinates to the fragment shader
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

)glsl";

const char* fragmentShaderSourceTexture = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal; // Received from vertex shader
in vec3 FragPos; // Received from vertex shader
in vec2 TexCoords; // Received from vertex shader

uniform vec3 lightPos; // Position of the light source in world space
uniform vec3 viewPos; // Position of the camera in world space
uniform vec3 lightColor; // Color of the light
uniform sampler2D texture1; // The texture sampler

void main() {
    // Texture color
    vec4 texColor = texture(texture1, TexCoords);

    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine the two components
    vec3 result = (ambient + diffuse) * vec3(texColor);
    FragColor = vec4(result, 1.0);
}

)glsl";

const char* vertexShaderSourceText = R"glsl(
#version 330 core
layout (location = 0) in vec4 vertex; // {x, y, z, w} -> {xpos, ypos, texCoords}

out vec2 TexCoords;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
)glsl";

const char* fragmentShaderSourceText = R"glsl(
#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main() {    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    FragColor = vec4(textColor, 1.0) * sampled;
}
)glsl";