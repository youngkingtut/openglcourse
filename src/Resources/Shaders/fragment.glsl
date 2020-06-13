#version 330

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

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

struct SpotLight {
   PointLight base;
   vec3 direction;
   float edge;
};

struct Material {
   float specularIntensity;
   float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;
uniform sampler2D theTexture;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
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

vec4 CalcPointLight(PointLight pLight) {
   vec3 direction = FragPos - pLight.position;
   float distance = length(direction);
   direction = normalize(direction);

   vec4 color = CalcLightByDirection(pLight.base, direction);
   float attenutation = pLight.exponent * distance * distance +
   pLight.linear * distance +
   pLight.constant;
   return color / attenutation;
}

vec4 CalcSpotLight(SpotLight sLight) {
   vec4 color = vec4(0, 0, 0, 0);
   vec3 rayDirection = normalize(FragPos - sLight.base.position);
   float slFactor = dot(rayDirection, sLight.direction);

   if(slFactor > sLight.edge) {
      color = CalcPointLight(sLight.base) * (1.0f - ( (1.0f - slFactor) * (1.0f / (1.0f - sLight.edge))));
   }

   return color;
}

vec4 CalcSpotLights() {
   vec4 totalColor = vec4(0, 0, 0, 0);

   for(int i = 0; i < spotLightCount; i++) {
      totalColor += CalcSpotLight(spotLights[i]);
   }

   return totalColor;
}

vec4 CalcPointLights() {
   vec4 totalColor = vec4(0, 0, 0, 0);

   for(int i = 0; i < pointLightCount; i++) {
      totalColor += CalcPointLight(pointLights[i]);
   }

   return totalColor;
}

void main() {
   color = texture(theTexture, TexCoord) * (CalcDirectionalLight() + CalcPointLights() + CalcSpotLights());
}
