#version 330 core

#define gamma 2.2

//consts
const vec3 ambient = vec3(0.1, 0.1, 0.1);
const vec2 poissonDisk[4] = vec2[](
        vec2( -0.94201624, -0.39906216 ),
        vec2( 0.94558609, -0.76890725 ),
        vec2( -0.094184101, -0.92938870 ),
        vec2( 0.34495938, 0.29387760 )
      );

//inputs
in vec2 tcoord; 
in vec3 norm;
in vec3 vpos;
in vec3 scoord;


//structs
struct Light{
	vec3 diffuseCoefficient;
	float intensity;
	vec3 att;
	vec3 pos;
};

//uniforms
uniform sampler2D diffuseMap;
uniform sampler2DShadow dLShadowMap;
uniform vec3 viewpos;
uniform Light lights[8];
uniform int light_amt;

uniform vec3 dLcolor;
uniform vec3 dLdirection;
uniform float dLintensity;


//outputs
layout(location = 0) out vec4 fragcolor;

//functions
vec4 texture_gamma(sampler2D tex, vec2 texcoord){
	vec4 texcol = texture(tex, texcoord);
	return vec4(pow(texcol.rgb, vec3(gamma)), texcol.a);
}

float shadowPoisson(){
    float fMap = 0;
    for (int i=0;i<4;i++){
    	float bias = 0.004*tan(acos(clamp(dot(norm, dLdirection), 0, 1)));
        bias = clamp(bias, 0,0.01);
        fMap += texture(dLShadowMap, vec3(scoord.xy + (poissonDisk[i]/2000.0), scoord.z - bias) );
    }
    fMap/=4;

    return fMap;
}

float shadowPCF(){
	float bias = 0.004*tan(acos(clamp(dot(norm, dLdirection), 0, 1)));
    bias = clamp(bias, 0,0.01);
    return texture(dLShadowMap, vec3(scoord.xy, scoord.z - bias));
}

void main(void) {
	vec3 lighting = vec3(0,0,0);
    //shadow
    float fMap = shadowPoisson();
    vec4 diffcolor = texture_gamma(diffuseMap, tcoord);
    vec3 dirView = normalize(viewpos - vpos);

	int i;
	for(i = 0; i < light_amt; i++){
		Light light = lights[i];

		if(light.intensity > 0){
			vec3 dirL = normalize(light.pos - vpos);

//			//diffuse
			float diffCoefficient = max(0.0, dot(norm, dirL));
			vec3 diffuse = diffCoefficient * diffcolor.rgb * light.intensity * light.diffuseCoefficient;
//
			//attenuation
			float dist = length(light.pos - vpos);
			float attenuation = 1.0 / (light.att.x + light.att.y * dist + light.att.z*dist*dist);
			lighting += attenuation*(diffuse);
		}
	}


	//Directional Light
	if(dLintensity > 0 && (fMap > 0) && dot(norm, dLdirection) > 0){
//
//			//diffuse
            float diffCoefficient = max(0.0, dot(norm, dLdirection));
            vec3 diffuse = fMap * diffcolor.rgb * dLintensity * dLcolor * diffCoefficient;
//

            lighting += diffuse;
    }
    //Ambient Lighting
    lighting += ambient*diffcolor.rgb;


//    //linear color (color before gamma correction)
    fragcolor = vec4(lighting, 1);
}