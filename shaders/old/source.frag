#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

void main()
{
   vec3 lightColor = vec3(0.7f, 1.0f, 0.7f);
   vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
   vec3 lightPos = vec3(0.0f, 0.5f, 0.5f);

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   //vec3 lightDir = vec3(0.0f, 0.5f, 0.5f);

   float diff = max(0.0, dot(norm, lightDir));
   vec3 diffuse = diff * lightColor;

   float ambientStrength = 0.1f;
   vec3 ambient = ambientStrength * lightColor;
   vec3 result = (ambient + diffuse) * objectColor;
   FragColor = vec4(result, 1.0f);
   //FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
   //FragColor = vec4(Normal * 0.5 + 0.5, 1.0);
}