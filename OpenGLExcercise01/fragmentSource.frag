#version 330 core	
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};


struct LightDirectional{
	vec3 pos;
	vec3 dirToLight;
	vec3 color;
};

struct LightPoint{
	vec3 pos;
	vec3 dirToLight;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot{
	vec3 pos;
	vec3 dirToLight;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
	float cosPhyInner;
	float cosPhyOutter;
};

uniform Material material;
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;

uniform vec3 objColor;
uniform vec3 ambientColor;

uniform vec3 cameraPos;

out vec4 FragColor;		

//计算平行光
vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera){
	vec3 result = vec3(0,0,1);

	//diffuse  max(dot(L,N),0)
	float diffuseIntenSity = max(dot(light.dirToLight,uNormal),0);
	vec3 diffuse = diffuseIntenSity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular pow(max(dot(R,dirToCamera),0),material.shininess)
	vec3 R = normalize(reflect(-lightD.dirToLight,uNormal));
	float specularIntenSity = pow(max(dot(R,dirToCamera),0),material.shininess);
	vec3 specular = specularIntenSity * lightD.color * texture(material.specular,TexCoord).rgb;
	result = diffuse + specular;
	return result;
}

//计算点光源
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera){
	vec3 result = vec3(0,1,0);

	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1/(light.constant + light.linear * dist + light.quadratic *(dist * dist));
	//diffuse
	float diffuseIntenSity = max(dot(normalize(light.pos - FragPos),uNormal),0) * attenuation;
	vec3 diffuse = diffuseIntenSity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos),uNormal));
	float specularIntenSity = pow(max(dot(R,dirToCamera),0),material.shininess) * attenuation;
	vec3 specular = specularIntenSity * lightD.color * texture(material.specular,TexCoord).rgb;

	result = diffuse + specular;
	return result;
}

vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera){
	vec3 result = vec3(0,0,1);
	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1/(light.constant + light.linear * dist + light.quadratic * (dist * dist));
	//
	float spotRatio;
	float cosTheta = dot(normalize(FragPos - light.pos),-light.dirToLight);

	if(cosTheta > light.cosPhyInner){
		spotRatio = 1.0;
	}
	else if(cosTheta > light.cosPhyOutter){
		spotRatio = (cosTheta - light.cosPhyOutter)/(light.cosPhyInner - light.cosPhyOutter);
	}
	else{
		spotRatio = 0;
	}
	//diffuse
	float diffuseIntenSity = max(dot(normalize(light.pos - FragPos),uNormal),0) * attenuation * spotRatio;
	vec3 diffuse = diffuseIntenSity * light.color * texture(material.diffuse,TexCoord).rgb;
	//specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos),uNormal));
	float specularIntenSity = pow(max(dot(R,dirToCamera),0),material.shininess) * attenuation * spotRatio;
	vec3 specular = specularIntenSity * light.color * texture(material.specular,TexCoord).rgb;

	result = diffuse + specular;
	return result;
}

void main(){
	
	vec3 finalResult = vec3(0,0,0);

	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);

	finalResult += CalcLightDirectional(lightD,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP0,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP1,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP2,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP3,uNormal,dirToCamera);
	finalResult += CalcLightSpot(lightS,uNormal,dirToCamera);

	//FragColor = vec4(finalResult,1.0f);
	FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}