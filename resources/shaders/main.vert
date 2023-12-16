uniform mat4 view;
uniform mat4 world;
uniform mat4 projection;
uniform mat4 worldIT;

in vec3 a_position;
in vec2 a_uv;
in vec3 a_normal;
in vec3 a_tangent;

out vec2 v_uv;
out vec3 v_pos;
out mat3 v_TBN;

mat3 create_TBN_mat(vec3 normal, vec3 tangent)
{
	vec3 N = normal;
	vec3 T = normalize( tangent - dot(tangent, N) * N);
	vec3 B = cross(N, T);

	return mat3(T,B,N);
}

void main() {
    gl_Position = projection * view * world * vec4(a_position, 1.0);
    v_uv = a_uv;
    v_pos = (world * vec4(a_position, 0.0)).xyz; 
    
    // TBN Matrix
    vec4 normal = worldIT * vec4(a_normal, 0.0);
    vec4 tangent = worldIT * vec4(a_tangent, 0.0);
    v_TBN = create_TBN_mat(normal.xyz, tangent.xyz);
}
