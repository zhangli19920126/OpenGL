#version 330 core
out vec4 FragColor;

in vec3 WPosition;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture1;
uniform samplerCube skybox;
uniform vec3 viewPos;
uniform float reflectionRate;

void main()
{    
    vec4 tex = texture(texture1, TexCoords);
    ////∑¥…‰
    //vec3 I = normalize(WPosition - viewPos);
    //vec3 R = reflect(I, normalize(Normal));
    //vec4 reflectionColor = vec4(texture(skybox, R).rgb, 1.0);
    //FragColor = tex * (1-reflectionRate) + reflectionColor * reflectionRate;
    //’€…‰
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(WPosition - viewPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    vec4 refractionColor = vec4(texture(skybox, R).rgb, 1.0);
    FragColor = tex * (1-reflectionRate) + refractionColor * reflectionRate;
}