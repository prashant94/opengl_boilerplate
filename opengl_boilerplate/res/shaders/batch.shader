#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec4 colour_coord;
layout(location = 3) in float tex_index;

out vec2 v_tex_coord;
out vec4 v_colour_coord;
out float v_tex_index;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * position;
    v_tex_coord = tex_coord;
    v_colour_coord = colour_coord;
    v_tex_index = tex_index;
};


#shader fragment
#version 460 core

layout(location = 0) out vec4 colour;

in vec2 v_tex_coord;
in vec4 v_colour_coord;
in float v_tex_index;

uniform vec4 u_colour;
uniform sampler2D u_textures[2];

void main()
{
    int index = int(v_tex_index);
    vec4 tex_colour  = texture(u_textures[index], v_tex_coord);
    colour = tex_colour;
    //colour = v_colour_coord;

};
