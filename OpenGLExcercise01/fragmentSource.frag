#version 330 core	
in vec3 FragPos;
in vec3 Normal;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;		

void main(){
	vec3 lightDir = normalize(lightPos-FragPos);
	vec3 diffuse = max(dot( lightDir,normalize(Normal)),0.0) * lightColor;
	//FragColor = vec4(objColor * ambientColor,1.0);
	FragColor = vec4((diffuse+ambientColor)*objColor,1.0);
}