uniform mat4 projection;

in vec2 a_position;
in vec3 a_color;

out vec4 v_color;

void main()
{
    gl_Position = projection * vec4(a_position, 0.0, 1.0);
	v_color = vec4(normalize(a_color), 1.0);
}
