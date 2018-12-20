#include "ObjectShader.h"
#include <iostream>
#include <fstream>

ObjectShader::ObjectShader()
{
}

void ObjectShader::init(const std::string& filename)
{
	program = glCreateProgram(); //creats shader program
	shaders[0] = CreateShader(LoadShader("..\\res\\\shader.vert"), GL_VERTEX_SHADER); //creats vertex shader
	shaders[1] = CreateShader(LoadShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); //creats fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]); //set shaders are added to the shader program
	}

	glBindAttribLocation(program, 0, "position"); //set position is atributed with the shader program
	glBindAttribLocation(program, 1, "texCoord"); //set tex coordinates are atributed with the shader program

	glLinkProgram(program); //executables are creted that will be run on graphics card shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader has failed to link program!"); //checks for necessary errors

	glValidateProgram(program); //makes sure that the program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader does not have valid program!");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform"); //makes sure that location of uniform is associated with the program 
}

ObjectShader::~ObjectShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]); //removes shaders from the program
		glDeleteShader(shaders[i]); //shaders are deleted
	}
	glDeleteProgram(program); //program is deleted
}

void ObjectShader::Bind()
{
	glUseProgram(program); //installs the program
}

void ObjectShader::Update(const ObjectTransform& transform, const PlayerCamera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint ObjectShader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //creats a set shader

	if (shader == 0) //if there is no shader loaded then
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //converts strings to lists of c strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //makes sure that source code is sent to opengl
	glCompileShader(shader); //compiles shader code within opengl

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error occured while compiling shader!"); //checks if there are any compile errors

	return shader;
}

std::string ObjectShader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Can not load shader: " << fileName << std::endl;
	}

	return output;
}

void ObjectShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

