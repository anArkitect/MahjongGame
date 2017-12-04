#version 400

out vec4 fragcolor;           

void main(void)
{   
   fragcolor = vec4(gl_PointCoord.xy, 0.0, 1.0);

   vec2 p = 2.0*(gl_PointCoord.xy-vec2(0.5));
   if(length(p)>=0.99 || length(p)<=0.85) discard;
   
   //fragcolor = vec4(length(p));

   fragcolor = vec4(length(p));
   fragcolor = vec4(fragcolor.rgb * vec3(1.0, 0.5, 0.1), 0.15);
}




















