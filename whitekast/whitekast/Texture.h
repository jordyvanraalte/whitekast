#pragma once

#include <string>
#include <windows.h>
#include <gl/GL.h>

class Texture
{
public:

	GLuint textureId;

	Texture(const std::string &filename);
	Texture();
	~Texture();
	void bind();
};
