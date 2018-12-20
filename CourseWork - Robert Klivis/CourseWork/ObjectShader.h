#pragma once
#include <string>
#include <GL\glew.h>
#include "ObjectTransform.h"
#include "PlayerCamera.h"

class ObjectShader
{
public:
	ObjectShader(); //constructor for ObjectShader

	void Bind(); //sets graphics crad to use the shader
	void Update(const ObjectTransform& transform, const PlayerCamera& camera); //update function for shader
	void init(const std::string& filename); //initlise function for shader

	std::string ObjectShader::LoadShader(const std::string& fileName);
	void ObjectShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint ObjectShader::CreateShader(const std::string& text, unsigned int type);

    ~ObjectShader(); //deconstructor for ObjectShader


protected:
private:
	static const unsigned int NUM_SHADERS = 2; //set number of shaders being used

	enum
	{
		TRANSFORM_U, //transform for uniforms

		NUM_UNIFORMS //number of uniforms
	};
	
	GLuint program; //tracks the program for shader
	GLuint shaders[NUM_SHADERS]; //tracks array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //number of uniforms that are available
};
