#version 330

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;

void main() {
   gl_Position = projection * view * model * vec4(position, 1.0);
   vertexColor = vec4(clamp(position.xy, 0.0f, 1.0f), 0.5f, 1.0f);
}
