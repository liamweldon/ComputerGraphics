#version 420
in vec3 fragPos;
in vec2 texCoords;

out vec4 fragColor;



uniform sampler2D textureDiffuse;


void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(textureDiffuse, texCoords);
}