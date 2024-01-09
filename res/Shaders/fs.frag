#version 460

in vec2 t_coords;
out vec4 frag_color;

uniform sampler2D tex;

void main()
{
   frag_color = texture2D(tex, t_coords);
   if (frag_color == vec4(0.0))
   {
		discard;
   }
}