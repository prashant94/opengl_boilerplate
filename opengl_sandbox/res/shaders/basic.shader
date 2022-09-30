#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex_coord;

out vec2 v_tex_coord;
out vec4 v_colour_coord;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * position;
    v_tex_coord = tex_coord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_tex_coord;

uniform vec4 u_colour;
uniform sampler2D u_texture;

void main()
{
    vec4 tex_colour = texture(u_texture, v_tex_coord);
    colour = tex_colour;
};
