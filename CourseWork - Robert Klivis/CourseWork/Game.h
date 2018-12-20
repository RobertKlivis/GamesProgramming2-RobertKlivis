#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "GameDisplay.h" 
#include "ObjectShader.h"
#include "ObjectMesh.h"
#include "ObjectTexture.h"
#include "ObjectTransform.h"
#include "Audio.h"
#include "PlayerCamera.h"
#include "GL/glut.h"

enum class GameState{PLAY, EXIT};

class Game
{
public:
	Game(); //constructor for game
	~Game(); //deconstructor for game

	void run();

private:

	void initSystems(); //initilise systems
	void processInput(); //process the inputs
	void gameLoop(); //set game loop
	void drawGame(); //draw for game
	void Collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad); //collision detection
	void playAudio(unsigned int Source, glm::vec3 pos); //play audio

	void drawText(const char *text, int length, int x, int y); //draw for text
	
	void transformObject(); //set object transformation

	GameDisplay gameDisplay;
	GameState gameState;
	ObjectMesh object1;
	ObjectMesh object2;
	ObjectMesh object3;
	PlayerCamera myCamera;
	ObjectTexture texture;
	ObjectTexture texture2;
	ObjectTexture texture3;
	ObjectShader shader;
	Audio audioDevice;
	ObjectMesh meshSphere;
	ObjectCollision mesh;

	float move; //float for the move counter

	float radius; //float for the radius

	bool fruit1; //boolean for fruit1
	bool fruit2; //boolean for fruit2
	bool fruit3; //boolean for fruit3
	bool fruit4; //boolean for fruit4
	bool fruit5; //boolean for fruit5

	bool collision;

	bool start; //boolean for start of the game
	bool win; //boolean for win stage of the game

	float d; //float for distance (collision)

	unsigned int BackgroundMusic; //unsigned integer fo background music
	unsigned int SplashSound; //unsigned integer for the splash sound

};
