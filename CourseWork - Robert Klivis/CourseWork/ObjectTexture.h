#pragma once
#include <string>
#include <GL\glew.h>

class ObjectTexture
{
public:
	ObjectTexture(); //ObjectTexture constructor

	void Bind(unsigned int unit); //bind to use textures
	void init(const std::string& fileName); //initlise for textures

	~ObjectTexture(); //ObjectTexture deconstructor

protected:
private:

	GLuint textureHandler;
};

