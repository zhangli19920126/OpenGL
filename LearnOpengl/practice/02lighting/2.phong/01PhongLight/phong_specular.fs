#version 330 core
out vec4 FragColor;

in vec3 WPos;
in vec3 WNormal;
  
uniform vec3 lightColor;
uniform vec3 baseColor;
uniform float ambientRate;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform float specularStrength;
uniform int specularPow;

void main()
{
    //»·¾³¹â 
    vec3 ambient = ambientRate * lightColor;

    //specular
    vec3 norm = normalize(WNormal);
    vec3 lightDir = normalize(lightPos - WPos);
    vec3 viewDir = normalize(cameraPos - WPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(halfDir, norm), 0.0), specularPow);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 finalColor = (ambient + specular) * baseColor;

    FragColor = vec4(finalColor, 1.0);
}