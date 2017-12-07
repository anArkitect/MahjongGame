#version 400

struct Material
{
	sampler2D tex;

	samplerCube cubemap;

	float shininess;
};


struct DirLight
{
	vec3 direction;
	
	vec3 ambientComponent;
	vec3 diffuseComponent;
	vec3 specularComponent;
};


struct PointLight
{
	vec3 position;

	vec3 ambientComponent;
	vec3 diffuseComponent; 
	vec3 specularComponent;

	float constantTermCoef;
	float linearTermCoef;
	float quadraticTermCoef;
};


struct SpotLight
{
	vec3 position;
	vec3 direction;
	
	vec3 ambientComponent;
	vec3 diffuseComponent;
	vec3 specularComponent;

	float constantTermCoef;
	float linearTermCoef;
	float quadraticTermCoef;

	float innerCutOff;		
	float outerCutOff;
};

const int NR_POINT_LIGHTS = 4;

vec3 getDirLight(DirLight dirLight);
vec3 getPointLight(PointLight pointLight);
vec3 getSpotLight(SpotLight spotLight);

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform Material material;
uniform vec3 viewPos;
uniform SpotLight spotLight;
uniform bool holdStatus;
uniform bool hoverOver;


void main()
{

    DirLight dirLight;
    PointLight pointLights[NR_POINT_LIGHTS];

    // default directional light
    dirLight.ambientComponent  = vec3(0.5);
    dirLight.diffuseComponent  = vec3(1.0);
    dirLight.specularComponent = vec3(1.0);
    dirLight.direction         = vec3(0.0, -1.0, 0.0);

    // default point light
    pointLights[0].position = vec3(-2.0,  3.0, 1.0);
    pointLights[1].position = vec3(-2.0, -3.0, 1.0);
    pointLights[2].position = vec3( 4.0,  3.0, 1.0);
    pointLights[3].position = vec3( 4.0,  3.0, 1.0);



	vec3 combinedLight = getDirLight(dirLight);

    
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
        pointLights[i].ambientComponent  = vec3(0.1);
        pointLights[i].diffuseComponent  = vec3(0.37, 0.62,  0.63);
        pointLights[i].specularComponent = vec3(1.0);

        pointLights[i].constantTermCoef  = 1.0;
	    pointLights[i].linearTermCoef    = 0.09;
	    pointLights[i].quadraticTermCoef = 0.032;

		//combinedLight += getPointLight(pointLights[i]);
	}
	
    if (holdStatus || hoverOver)
	    combinedLight += getSpotLight(spotLight);
	
	FragColor = vec4(combinedLight, 1.0);
    //FragColor = texture(material.tex, TexCoords);
}



vec3 getDirLight(DirLight dirLight)
{
	vec3 norm       = normalize(Normal);
	vec3 lightDir   = normalize(-dirLight.direction);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 viewDir    = normalize(viewPos - FragPos);

	// ambient
	vec3 ambientLight = dirLight.ambientComponent * texture(material.tex, TexCoords).rgb;

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseLight = dirLight.diffuseComponent * diff * texture(material.tex, TexCoords).rgb;

	// specular
	vec3 rv = reflect(-viewDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularLight = dirLight.specularComponent * spec * texture(material.cubemap, rv, (material.shininess-2.0)*0.1).rgb;

	return ambientLight + diffuseLight + specularLight;
}


vec3 getPointLight(PointLight pointLight)
{

	vec3 norm       = normalize(Normal);
	vec3 lightDir   = normalize(pointLight.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 viewDir    = normalize(viewPos - FragPos);

	float distance = length(pointLight.position - FragPos);
	float attenuation = 1.0f / (pointLight.constantTermCoef + 
								pointLight.linearTermCoef * distance +
								pointLight.quadraticTermCoef * pow(distance, 2));
	
	// ambient
	vec3 ambientLight = pointLight.ambientComponent * texture(material.tex, TexCoords).rgb;

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseLight = pointLight.diffuseComponent * diff * texture(material.tex, TexCoords).rgb;

	// specular
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularLight =  pointLight.specularComponent * spec * texture(material.tex, TexCoords).rgb;

	return  (ambientLight + diffuseLight + specularLight);
}


vec3 getSpotLight(SpotLight spotLight)
{
	vec3 norm       = normalize(Normal);
	vec3 lightDir   = normalize(spotLight.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 viewDir    = normalize(viewPos - FragPos);

	// attenuation
	float distance = length(spotLight.position - FragPos);
	float attenuation = 1.0f / (spotLight.constantTermCoef + 
								spotLight.linearTermCoef * distance +
								spotLight.quadraticTermCoef * pow(distance, 2));

	// spot intensity
	vec3 spotDir = spotLight.direction;
	float intensity = (dot(-lightDir, spotDir) - spotLight.outerCutOff) / (spotLight.innerCutOff - spotLight.outerCutOff);
	intensity = clamp(intensity, 0.0f, 1.0f);
   

	// ambient
    vec3 ambientLight = intensity * spotLight.ambientComponent * texture(material.tex, TexCoords).rgb;
	// diffuse
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseLight = spotLight.diffuseComponent * diff * texture(material.tex, TexCoords).rgb;

	// specular
	vec3 rv = reflect(-viewDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specularLight = spotLight.specularComponent * spec * texture(material.cubemap, rv, (material.shininess-2.0)*0.1).rgb;


	return (ambientLight + diffuseLight + specularLight) * attenuation * intensity;
}

