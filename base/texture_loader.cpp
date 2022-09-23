#include "texture_loader.h"
#include <stb/stb_image.h>
#include <glad/glad.h>

unsigned int gl::load_texture_2d(const string& file)
{
	unsigned int id = 0;
	glGenTextures(1, &id);
	int width, height, nrComponents;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		if (nrComponents == 3)
			format = GL_RGB;
		if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	stbi_image_free(data);
	return id;
}

unsigned int gl::load_texture_3d(const string& file)
{
	return 0;
}

