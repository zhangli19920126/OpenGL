#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    int shininess;
    float diffuseStrength;
    float specularStrength;
    float ambient;
    float emissionRate;
}; 

struct Light {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light pointLight;
uniform vec3 cameraPos;

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoords;

void main()
{
    //Light Map
    vec3 baseColor = vec3(texture(material.diffuse, TexCoords));
    vec3 speculColr = vec3(texture(material.specular, TexCoords));
    vec3 emissionColor = vec3(texture(material.emission, TexCoords));

    //point light
    float distance = length(pointLight.position - WorldPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
    vec3 lightColor = pointLight.color * attenuation;

    //ambient
    vec3 ambient = lightColor * (baseColor  + emissionColor * material.emissionRate) * material.ambient;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(pointLight.position - WorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * (baseColor + emissionColor * material.emissionRate) * material.diffuseStrength;
    
    // specular
    vec3 viewDir = normalize(cameraPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * spec * speculColr * material.specularStrength; 
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}