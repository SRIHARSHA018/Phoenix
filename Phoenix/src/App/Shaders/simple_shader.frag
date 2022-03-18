#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

//camera position
uniform vec3 u_viewPosition;

//material struct
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

//Atenuation fact
struct Attenuation{
    float constant;
    float linear;
    float quadratic;
};

//light struct
struct Light{
   // vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//Directional Light struct
struct DirectionalLight{
    vec3 direction;
    Light props;
};
//PointLight struct
struct PointLight{
    vec3 position;
    Light props;
    Attenuation attenuationProps;
};

//Spot Light struct
struct SpotLight{
    vec3 position;
    vec3 direction;
    
    Light props;
    Attenuation attenuationProps;

    float cutOff;
    float outerCutOff;
};

uniform Material u_material;
uniform Light u_light;
uniform DirectionalLight u_dirLight;
uniform PointLight u_pointLight;
uniform SpotLight u_spotLight;

vec3 calDirectionalLight(DirectionalLight light,vec3 normal,vec3 viewDir);
vec3 calPointLight(PointLight light,vec3 normal,vec3 viewDir);
vec3 calSpotLight(SpotLight light,vec3 normal,vec3 viewDir);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(u_viewPosition-FragPos);

    
    vec3 result = calDirectionalLight(u_dirLight,normal,viewDir);
    result += calPointLight(u_pointLight,normal,viewDir);
    result += calSpotLight(u_spotLight,normal,viewDir);
    FragColor = vec4(result,1.0);
    
}
vec3 calDirectionalLight(DirectionalLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir = normalize(light.direction);

    float diffuseWeight = max(dot(normalize(normal),lightDir),0.0);
    
    vec3 reflectDir = normalize(reflect(-lightDir,  normalize(normal)));
    float specularWeight = pow(max(dot(viewDir,reflectDir),0.0),u_material.shininess);


    vec3 ambient = light.props.ambient * vec3(texture(u_material.diffuse,TexCoord));
    vec3 diffuse = light.props.diffuse*diffuseWeight* vec3(texture(u_material.diffuse,TexCoord));
    vec3 specular = light.props.specular * specularWeight* vec3(texture(u_material.specular,TexCoord));

    return (ambient+diffuse+specular);
}
vec3 calPointLight(PointLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);

    float diffuseWeight = max(dot(normalize(normal),lightDir),0.0);
    
    vec3 reflectDir = reflect(-lightDir,normalize(normal));
    float specularWeight = pow(max(dot(viewDir,reflectDir),0.0),u_material.shininess);

    //Attenuation
    float dist = length(light.position - FragPos);
    float attenuation =   1.0/(light.attenuationProps.constant  + light.attenuationProps.linear* dist * light.attenuationProps.quadratic * dist * dist);


    vec3 ambient = light.props.ambient * vec3(texture(u_material.diffuse,TexCoord));
    vec3 diffuse = light.props.diffuse*diffuseWeight* vec3(texture(u_material.diffuse,TexCoord));
    vec3 specular = light.props.specular * specularWeight* vec3(texture(u_material.specular,TexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular*= attenuation;
    return (ambient + diffuse + specular);
}


vec3 calSpotLight(SpotLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);

    float diffuseWeight = max(dot(normalize(normal),lightDir),0.0);
    
    vec3 reflectDir = reflect(-lightDir,normalize(normal));
    float specularWeight = pow(max(dot(viewDir,reflectDir),0.0),u_material.shininess);

    //Attenuation
    float dist = length(light.position - FragPos);
    float attenuation =   1.0/(light.attenuationProps.constant  + light.attenuationProps.linear* dist * light.attenuationProps.quadratic * pow(dist,2));

    //cone angles setup
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.props.ambient * vec3(texture(u_material.diffuse,TexCoord));
    vec3 diffuse = light.props.diffuse*diffuseWeight* vec3(texture(u_material.diffuse,TexCoord));
    vec3 specular = light.props.specular * specularWeight* vec3(texture(u_material.specular,TexCoord));

    ambient *= attenuation *intensity;
    diffuse *= attenuation *intensity; 
    specular*= attenuation *intensity;

    return (ambient + diffuse + specular);
}