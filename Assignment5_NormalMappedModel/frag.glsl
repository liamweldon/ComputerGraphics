#version 330
in vec3 fragPos;
in vec3 normCoords;
in vec2 texCoords;

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

uniform sampler2D textureDiffuse;
uniform sampler2D textureNorm;
uniform mat4 viewMatrix;
uniform PointLight pointLights[1];  // Our lights

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  fragColor = texture(textureDiffuse, texCoords);
  vec3 normal = texture(textureNorm, texCoords).xyz;

  vec3 diffuseColor = fragColor.rgb;

  vec3 ambient = vec3(0.0, 0.0, 0.0);
  vec3 diffuseLight = vec3(0.0, 0.0, 0.0);
  vec3 specular = vec3(0.0, 0.0, 0.0);

  int size = 1;

  for (int i = 0; i < size; i++) {
    ambient += pointLights[i].ambientIntensity * pointLights[i].color;

    vec3 lightDir = normalize(pointLights[i].position - fragPos);
    float diffImpact = max(dot(normal, lightDir), 0.0);
    diffuseLight += diffImpact * pointLights[i].color;

    
    mat4 viewInverse = inverse(viewMatrix);
    vec3 viewPos = vec3(viewInverse[0][3], viewInverse[1][3], viewInverse[2][3]);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    specular += pointLights[i].specularIntensity * spec * pointLights[i].color;  
  }


  vec3 lighting = diffuseLight + ambient + specular;

  fragColor = vec4(diffuseColor * lighting, 1.0 );
    
}