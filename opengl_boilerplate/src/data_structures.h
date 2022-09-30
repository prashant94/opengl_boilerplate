#pragma once

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Vertex
{
	Vec2 positions;
	Vec2 tex_coords;
	Vec4 colour;
	float tex_index;
};