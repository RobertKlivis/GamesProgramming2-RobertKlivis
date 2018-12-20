#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "ObjectTransform.h"

struct ObjectVertex
{
public:
	ObjectVertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; } //position getter
	glm::vec2* GetTexCoord() { return &texCoord; } //tex coordinate getter
	glm::vec3* GetNormal() { return &normal; } //getter for normal
	

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct ObjectCollision
{
public:

	ObjectCollision(); //ObjectCollision constructor
	~ObjectCollision(); //ObjectCollision deconstructor

	void meshSphere(const glm::vec3& position, float);
	
	ObjectCollision(const glm::vec3& position, float)
	{
		this->position = position;
		this->radius = radius;

	}


	glm::vec3* GetPosition() { return &position; } //position getter

	float GetRadius() { return radius; } //getter for float of the radius

private:

	glm::vec3 position;
	float radius; //float for the radius

};



class ObjectMesh
{
public:
	ObjectMesh(); //constructor for ObjectMesh
	~ObjectMesh(); //deconstructor for ObjectMesh

	void draw(); //draw funciton
	void init(ObjectVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); //initlise function
	void loadModel(const std::string& filename); //load models
	void initModel(const IndexedModel& model); //initlise models

	ObjectCollision meshSphere;

private:

	enum
	{
		POSITION_VERTEXBUFFER, //position vertex buffer
		TEXCOORD_VB, //tex coordinate vertex buffer
		NORMAL_VB, //vertex buffer for normal
		INDEX_VB, //vertex buffer for index
		NUM_BUFFERS //number of buffers
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; //creats array for buffers
	unsigned int drawCount; //set number for amount of vertex array objects to draw
};
