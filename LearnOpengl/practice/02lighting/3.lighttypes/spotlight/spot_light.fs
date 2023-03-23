#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuseTex;
    sampler2D specularTex;
    sampler2D emissionTex;
    float emission;
    float ambient;
    int shininess;
    float diffuse;
    float specular;
}; 

struct SpotLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform SpotLight light;
uniform vec3 viewPos;

in vec3 WorldPos;
in vec3 Normal;
in vec2 TexCoords;

void main()
{
     float distance = length(light.position - WorldPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
     vec3 lightColor = light.color * attenuation;
     vec3 baseColor = vec3(texture(material.diffuseTex, TexCoords));

     vec3 lightDir = normalize(light.position - WorldPos);
     vec3 ambient = lightColor * material.ambient * baseColor;

     float theta = dot(lightDir, normalize(-light.direction));
     float epsilon = light.cutOff - light.outerCutOff;
     float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

     vec3 specularColor = vec3(texture(material.specularTex, TexCoords));
     vec3 emissionColor = vec3(texture(material.emissionTex, TexCoords));

     //diffuse
     vec3 norm = normalize(Normal);
     vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor * baseColor * material.diffuse;

     //specular
     vec3 viewDir = normalize(viewPos - WorldPos);
     vec3 half = normalize(lightDir + viewDir);
     float specularShiness = pow(max(dot(half, norm), 0.0), material.shininess);
     vec3 specular = specularShiness * specularColor * lightColor * material.specular;

     vec3 finalColor = (diffuse + specular) * intensity + ambient;
     FragColor = vec4(finalColor, 1.0);
} 