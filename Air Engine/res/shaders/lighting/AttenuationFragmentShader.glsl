#version 330 core

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float linear;
	float quadratic;
};

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;

	vec3 specular;
	float shininess;
};

uniform int phong = 0;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec4 out_Color;
in vec2 out_TexCoord;
in vec3 out_Normal;
in vec3 out_FragPos;

out vec4 color;

void main() {
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	//color = out_Color;
	float distance = length(light.position - out_FragPos);
	//float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));
	float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance));
	//float attenuation = 1.0 / distance;

	vec3 normal = normalize(out_Normal);
	vec3 lightDir = normalize(light.position - out_FragPos);
	//vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(lightDir, normal), 0.0);

	vec4 diffuseColor = texture(material.texture_diffuse1, out_TexCoord);

	if (diffuseColor.a < 0.5)
		discard;

	vec3 diffuse = diff * vec3(diffuseColor) * light.diffuse;
	diffuse *= attenuation;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - out_FragPos);

	vec3 halfwayDir = normalize(viewDir + lightDir);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	
	float spec = 0.0f;
	if(phong == 1)//Phong
		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess / 4.0);
	else//Blinn phong
		float spec = pow(max(dot(out_Normal, halfwayDir), 0.0), material.shininess);
	
	vec3 specular = spec * vec3(texture(material.texture_specular1, out_TexCoord)) * light.specular;
	specular *= attenuation;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * vec3(texture(material.texture_diffuse1, out_TexCoord)) * light.ambient;
	ambient *= attenuation;

	vec3 result = /*texture(texture_diffuse1, out_TexCoord).xyz **/ (ambient + diffuse + specular);
	color = vec4(result, 1.0);
	//color = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
}
