#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float diffuseStrength;
    float specularStrength;
    float shininess;
    float emissionStrength;
}; 

struct DirLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;

    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir);

#define NR_POINT_LIGHTS 4
#define NR_SPOT_LIGHTS 4

in vec3 WorldPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform Material material;

void main()
{ 
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - WorldPos)

    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLight, norm, WorldPos, viewDir);
    }

    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
    {
        result += CalcSpotLight(SpotLight spotLight, norm, WorldPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, Material material)
{
    //diffuse NL
    vec3 lightDir = normalize(-light.direction);
    vec3 diffuseTex = vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = max(dot(lightDir, normal), 0.0) * diffuseTex * light.color * material.diffuseStrength;

    //speclur 
    vec3 half = normalize(lightDir + viewDir);
    vec3 NH = max(dot(normal, half),0.0); 
    vec3 specularTex = vec3(texture(material.specular, TexCoords));
    vec3 specular = pow(NH, material.shininess) * specularTex * light.color *  material.specularStrength;

    //ambient
    vec3 emission = vec3(texture(material.emission, TexCoords)) * emissionStrength;

    return (emission + diffuse + specular);
}