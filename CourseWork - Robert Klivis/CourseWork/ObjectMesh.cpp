#include "ObjectMesh.h"
#include <vector>

void ObjectMesh::init(ObjectVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}

	for (unsigned int i = 0; i < numVertices; i++)
		model.indices.push_back(indices[i]);

	initModel(model); //initlise the model
}

void ObjectMesh::initModel(const IndexedModel& model)
{
	
	drawCount = model.indices.size(); //set draw count to model indices size

	glGenVertexArrays(1, &vertexArrayObject); //generates vertex array and stores it into the vertex array object
	glBindVertexArray(vertexArrayObject); //bind the vertex array object

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generates the buffer based on array of data and buffers
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //makes sure that opengl knows the type of data that the buffer is
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //moves the necessary data to the graphics card
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //makes sure that opengl knows the type of data is and passes it
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //and movies it to the graphics card
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); //tells oppengl what type of data buffer is
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //then passes it to the graphics card

	glBindVertexArray(0); //unbinds set vertex array object

}

ObjectMesh::ObjectMesh()
{
	drawCount = NULL; //set draw count to null
}

void ObjectMesh::loadModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initModel(model); //initlise model
}

ObjectMesh::~ObjectMesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); //deletes all the necessary arrays
}

void ObjectMesh::draw()
{
	glBindVertexArray(vertexArrayObject); //bind vertex array object
	
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0); //draw elements
	
	glBindVertexArray(0);
}

ObjectCollision::ObjectCollision()
{

}

ObjectCollision::~ObjectCollision()
{

}

void ObjectCollision::meshSphere(const glm::vec3& position, float)
{

	this->position = position;
	this->radius = radius;

}
