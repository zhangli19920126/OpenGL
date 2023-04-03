#version 330 core
out vec4 FragColor;

struct DirLight {
    vec3 color;
    vec3 direction;
};

struct PointLight {
    vec3 color;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
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

#define NR_POINT_LIGHTS 3

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform float shininess;
uniform float ambientRate;
uniform float diffuseRate;
uniform float specRate;
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform float dirLightRate;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform float pointRate[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform float spotLightRate;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float rate);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{   
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - WorldPos);
    
    //direction light
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, WorldPos, viewDir, pointRate[i]);    
    // phase 3: spot light
    result += CalcSpotLight(spotLight, norm, WorldPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}


// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 baseColor = vec3(texture(texture_diffuse1, TexCoords));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 half = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, half), 0.0), shininess);
    vec3 lightColor = light.color;
    
    // combine results
    vec3 ambient = baseColor * ambientRate;
    vec3 diffuse = diff * baseColor * diffuseRate;
    vec3 specular = spec * vec3(texture(texture_specular1, TexCoords)) * specRate;
    return (ambient + diffuse + specular) * lightColor * dirLightRate;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float rate)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 lightColor = light.color;
    vec3 baseColor = vec3(texture(texture_diffuse1, TexCoords));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 half = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, half), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = lightColor * baseColor* ambientRate;
    vec3 diffuse = lightColor * diff * baseColor * diffuseRate;
    vec3 specular = lightColor * spec * vec3(texture(texture_specular1, TexCoords))* specRate;

    return (ambient + diffuse + specular) * attenuation * rate;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 lightColor = light.color;
    vec3 baseColor = vec3(texture(texture_diffuse1, TexCoords));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 half = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, half), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = lightColor * baseColor * ambientRate;
    vec3 diffuse = lightColor * diff * baseColor * diffuseRate;
    vec3 specular = lightColor * spec * vec3(texture(texture_specular1, TexCoords)) * specRate;

    return (ambient + diffuse + specular) * attenuation * intensity * spotLightRate;
}