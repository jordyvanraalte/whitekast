#include "Texture.h"
#include "stbi.h"

Texture::Texture(const std::string &filename)
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * imgData = stbi_load(filename.c_str(), &width, &height, &bpp, 4);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData);
	stbi_image_free(imgData);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::~Texture()
{

}

Texture::Texture()
{

}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
