#version 330 core
out vec4 FragColor;

in vec3 WPos;
in vec3 WNormal;
  
uniform vec3 lightColor;
uniform vec3 baseColor;
uniform float ambientRate;
uniform vec3 lightPos;

void main()
{
    //»·¾³¹â 
    vec3 ambient = ambientRate * lightColor;

    //diffuse
    vec3 norm = normalize(WNormal);
    vec3 lightDir = normalize(lightPos - WPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 finalColor = (ambient + diffuse) * baseColor;

    FragColor = vec4(finalColor, 1.0);
}