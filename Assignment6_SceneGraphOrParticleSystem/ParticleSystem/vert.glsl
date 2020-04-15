#version 420
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


out vec3 fragPos;
out vec2 texCoords;

void main()
{
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);

    fragPos = position;
    texCoords = textureCoords;
}