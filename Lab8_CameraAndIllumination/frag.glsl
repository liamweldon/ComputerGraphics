#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// And our normal
in vec3 norm;
// And our fragment position for lighting
in vec3 fragPos;

// We always define a fragment color that we output.
out vec4 fragColor;

// Define our light(s)
struct PointLight {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture
uniform mat4 view;                  // we need the view matrix for highlights
uniform PointLight pointLights[3];  // Our lights

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(tex, texCoords);
  vec3 diffuseColor = fragColor.rgb;

  vec3 ambient = vec3(0.0, 0.0, 0.0);
  vec3 diffuseLight = vec3(0.0, 0.0, 0.0);
  vec3 specular = vec3(0.0, 0.0, 0.0);;

  // all attempts at calculating size programatically were met with OpenGL resistance
  int size = 3;

  for (int i = 0; i < size; i++) {
    ambient += pointLights[i].ambientIntensity * pointLights[i].color;

    vec3 lightDir = normalize(pointLights[i].position - fragPos);

    float diffImpact = max(dot(norm, lightDir), 0.0);
    diffuseLight += diffImpact * pointLights[i].color;

    mat4 viewInverse = inverse(view);
    vec3 viewPos = vec3(viewInverse[0][3], viewInverse[1][3], viewInverse[2][3]);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    specular += pointLights[i].specularIntensity * spec * pointLights[i].color;
  
  }


  vec3 lighting = diffuseLight + ambient + specular;

  fragColor = vec4(diffuseColor * lighting, 1.0 );
    
}