#version 460

in vec2 t_coords;
out vec4 frag_color;
uniform bool is_mirror;


uniform sampler2D tex;

void main()
{
	vec2 tex_coords = t_coords;
	if (is_mirror)
	{
        tex_coords.x = 1.0 - tex_coords.x;
	}

	frag_color = texture2D(tex, tex_coords);

   
   
   

   if (frag_color == vec4(0.0))
   {
		discard;
   }
}