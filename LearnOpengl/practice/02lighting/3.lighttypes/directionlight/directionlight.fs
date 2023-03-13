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
    vec3 direction;
    vec3 color;
};

uniform Material material;
uniform Light light;
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
    //ambient
    vec3 ambient = light.color * (baseColor  + emissionColor * material.emissionRate) * material.ambient;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.color * diff * (baseColor + emissionColor * material.emissionRate) * material.diffuseStrength;
    
    // specular
    vec3 viewDir = normalize(cameraPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * spec * speculColr * material.specularStrength; 
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}