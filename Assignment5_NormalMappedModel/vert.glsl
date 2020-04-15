#version 420
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalCoords;
layout(location = 2) in vec2 textureCoords;
// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out mat4 tbn;
out vec3 fragPos;
out vec3 normCoords;
out vec2 texCoords;

void main()
{
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);

    fragPos = position;
    normCoords = normalCoords;
    texCoords = textureCoords;
}