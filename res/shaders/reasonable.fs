#version 330 core

in vec2 tcoord; 
in vec3 norm;
in vec3 vpos;

uniform sampler2D texture0;
uniform vec3 viewpos;

uniform vec3 material_specularCoefficient;
uniform vec3 material_diffuseCoefficient;
uniform float material_shininess;


layout(location = 0) out vec4 fragcolor;

struct Light{
	vec3 diffuseCoefficient;
	float intensity;
	vec3 specularCoefficient;
	vec3 att;
	vec3 pos;
};

uniform Light lights[8];
uniform int light_amt;

uniform vec3 ambientLighting;

const float gamma = 2.2;

vec4 texture_gamma(sampler2D tex, vec2 texcoord){
	vec4 texcol = texture(tex, texcoord);
	return vec4(pow(texcol.rgb, vec3(gamma)), texcol.a);
}

void main(void) {
	vec3 lighting = vec3(0,0,0);
	//light.color = vec3(1, 1, 1);
	//light.intensity = 1;
	//light.phong_index = vec3(0.1, 1, 1);
	//light.att = vec3(1, 0.1, 0.001);
	//light.pos = vec3(0, 2, 0);
    vec4 texcolor = texture_gamma(texture0, tcoord);
	int i;
	vec3 ambient = ambientLighting * texcolor.rgb;
	for(i = 0; i < light_amt; i++){
		Light light = lights[i];
		
		if(light.intensity > 0){
			vec3 dirL = normalize(light.pos - vpos);	
			vec3 dirView = normalize(viewpos - vpos);

			//diffuse
			float diffCoefficient = max(0.0, dot(norm, dirL));
			vec3 diffuse = diffCoefficient * texcolor.rgb * light.intensity * light.diffuseCoefficient;

			//specular
			float specCoefficient = 0.0;
			if(diffCoefficient > 0.0)
			specCoefficient = pow(max(0.0, dot(dirView, reflect(-dirL, norm))), material_shininess);
			vec3 specular = specCoefficient * material_specularCoefficient * light.intensity * light.specularCoefficient;

			//attenuation
			float dist = length(light.pos - vpos);
			float attenuation = 1.0 / (light.att.x + light.att.y * dist + light.att.z*dist*dist);
			lighting += attenuation*(diffuse + specular);
		}
	}
    //linear color (color before gamma correction)
    fragcolor = vec4(ambient + lighting, texcolor.a);
}