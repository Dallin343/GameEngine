#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec2 v_TexCoord;
out vec3 v_Position;
out vec3 v_Normal;

void main() {

    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    v_Position = vec3(u_Model * vec4(a_Position, 1));
    v_TexCoord = a_TexCoord;

    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D u_MaterialDiffuse;
uniform sampler2D u_MaterialSpecular;
uniform float u_MaterialShininess;

uniform vec3 u_LightPosition;
uniform vec3 u_LightAmbient;
uniform vec3 u_LightDiffuse;
uniform vec3 u_LightSpecular;

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewPosition;

in vec2 v_TexCoord;
in vec3 v_Position;
in vec3 v_Normal;

void main() {
    vec3 ambient = u_Light.ambient * texture(u_Material.diffuse, v_TexCoord).rgb;

    //Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Light.position - v_Position);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoord));


    //Specular
    vec3 viewDir = normalize(u_ViewPosition - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = u_Light.specular * (spec * vec3(texture(u_Material.specular, v_TexCoord)));


    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
    //color = vec4(1.0f, 0.6f, 0.2f, 1.0f);
}
