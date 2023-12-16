uniform sampler2D u_tex;
uniform sampler2D u_normalMap;
uniform sampler2D u_specularMap;

// Scene properties
uniform vec3 u_lightDir;
uniform vec3 u_lightColor;
uniform float u_ambienceLevel;
uniform vec3 u_viewPos;

in vec2 v_uv;
in vec3 v_pos;

in mat3 v_TBN;

out vec4 PixelColor;

void main()
{   
    // Block
    vec4 block = texture(u_tex, v_uv);
    vec3 diffuseMat = block.rgb;
    
    // Normal Map Calculations
    vec3 normalMapSample = texture(u_normalMap, v_uv).rgb;
    vec3 nT = 2.0 * normalMapSample - 1.0;
	vec3 n = v_TBN * nT;

    // Ambient
    vec3 ambient = diffuseMat * u_ambienceLevel;

    // Diffuse
    float diff = max(dot(n, u_lightDir), 0.0);
    vec3 diffuse = diffuseMat * u_lightColor * diff;  

    // Specular
    vec3 viewDir = normalize(u_viewPos - v_pos);
    vec3 reflectDir = reflect(-u_lightDir, n);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 specular = spec * texture(u_specularMap, v_uv).rgb * u_lightColor * (ambient - 0.1);

	// Combine the components
    vec3 light = clamp(diffuse + specular, 0, 1);

    vec3 color = vec3(0,0,0);
    color += ambient;
    color += light;
    PixelColor = vec4(color, block.a);
} 




