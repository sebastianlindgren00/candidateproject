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

const char* vertexShaderSourceMaterial = R"glsl(
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

const char* fragmentShaderSourceMaterial = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal; 
in vec3 FragPos; 
in vec2 TexCoords; 

uniform float ambientStrength;
uniform vec3 lightColor;
uniform sampler2D texture1;

void main() {
    vec3 ambient = ambientStrength * lightColor;
    vec4 texColor = texture(texture1, TexCoords);
    vec3 result = ambient * vec3(texColor); // Combine ambient lighting with texture color
    FragColor = texture(texture1, TexCoords);
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
    FragColor = vec4(textColor, texture(text, TexCoords).r);
}
)glsl";

const char* vertexShaderSourceFisheye = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    TexCoord = aTexCoord;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
)glsl";

const char* fragmentShaderSourceFisheye = R"glsl(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D screenTexture;

void main() {
    vec2 uv = TexCoord * 2.0 - 1.0; // Map texture coordinates from [0,1] to [-1,1]
    float radius = length(uv);
    if (radius > 1.0) discard; // Discard fragment outside the circle

    // Fisheye effect
    float z = sqrt(1.0 - radius * radius);
    vec2 uvDistorted = uv * (1.0 / z);
    
    // Optionally you can re-normalize to [0,1] if needed
    // uvDistorted = uvDistorted * 0.5 + 0.5;

    FragColor = texture(screenTexture, uvDistorted);
}
)glsl";

//test for plain plane

const char* vertexShaderSourcePlain = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos; // Position of vertices

uniform mat4 projection;
uniform mat4 modelView;

void main() {
    gl_Position = projection * modelView * vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSourcePlain = R"glsl(
#version 330 core
out vec4 FragColor;

uniform vec3 planeColor; // Uniform color for the plane

void main() {
    FragColor = vec4(planeColor, 1.0);
}
)glsl";


//For the text texture
const char* vertexShaderSourceTextTexture = R"glsl(
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out vec2 vTexCoords;

uniform mat4 projection;
uniform mat4 modelView;

void main() {
    gl_Position = projection * modelView * vec4(position, 1.0);
    vTexCoords = texCoords;
}
)glsl";



const char* fragmentShaderSourceTextTexture = R"glsl(
#version 330 core
in vec2 vTexCoords;  // Read the texture coordinates from the vertex shader
out vec4 FragColor;  // Output color

uniform sampler2D text;  // Texture sampler uniform

void main() {
    vec4 texColor = texture(text, vTexCoords);
    if (texColor.a == 0.0) {
        discard;  // Skip fully transparent pixels
    }
    FragColor = texColor;
}
)glsl";