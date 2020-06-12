#version 330

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;

struct Light {
   vec3 color;
   float ambientIntensity;
   float diffuseIntensity;
};

struct DirectionalLight {
   Light base;
   vec3 direction;
};

struct PointLight {
   Light base;
   vec3 position;
   float constant;
   float linear;
   float exponent;
};

struct Material {
   float specularIntensity;
   float shininess;
};

uniform int pointLightCount;
uniform sampler2D theTexture;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform Material material;

uniform vec3 eyePosition;

vec4 CalcLightByDirection(Light light, vec3 direction) {
   vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

   float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
   vec4 diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

   vec4 specularColor = vec4(0, 0, 0, 0);

   if(diffuseFactor > 0) {
      vec3 fragToEye = normalize(eyePosition - FragPos);
      vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));

      float specularFactor = dot(fragToEye, reflectedVertex);

      if(specularFactor > 0) {
         specularFactor = pow(specularFactor, material.shininess);
         specularColor = vec4(light.color, 1.0f) * material.specularIntensity * specularFactor;
      }
   }

   return ambientColor + diffuseColor + specularColor;
}

vec4 CalcDirectionalLight() {
   return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalcPointLights() {
   vec4 totalColor = vec4(0, 0, 0, 0);

   for(int i = 0; i < pointLightCount; i++) {
      vec3 direction = FragPos - pointLights[i].position;
      float distance = length(direction);
      direction = normalize(direction);

      vec4 color = CalcLightByDirection(pointLights[i].base, direction);
      float attenutation = pointLights[i].exponent * distance * distance +
                           pointLights[i].linear * distance +
                           pointLights[i].constant;
      totalColor += color / attenutation;
   }

   return totalColor;
}

void main() {
   color = texture(theTexture, TexCoord) * (CalcDirectionalLight() + CalcPointLights());
}
