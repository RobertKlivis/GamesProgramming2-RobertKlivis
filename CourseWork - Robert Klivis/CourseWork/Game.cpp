#include "Game.h"
#include "PlayerCamera.h"
#include <iostream>
#include <string>


ObjectVertex vertices[] = { ObjectVertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					ObjectVertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					ObjectVertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

ObjectTransform transform;

Game::Game()
{
	gameState = GameState::PLAY; //set game state to play
	GameDisplay* gameDisplay = new GameDisplay(); //set a new game display
    ObjectMesh* object1();
	ObjectMesh* object2();
	ObjectMesh* object3();
	ObjectTexture* texture();
	ObjectTexture* texture2();
	ObjectTexture* texture3();
	ObjectShader* shader();
	ObjectMesh* Collision();
	Audio* audioDevice();
	ObjectMesh* meshSphere();
	ObjectCollision mesh();

}

Game::~Game()
{
}

void Game::run()
{
	initSystems(); //initilise systems on run
	gameLoop(); //initilise game loop on run

}

void Game::initSystems()
{
	gameDisplay.initDisplay(); //initilise game display


	object1.loadModel("..\\res\\banana.obj"); //Load model for banana.obj as mesh1


	object2.loadModel("..\\res\\Apple.obj"); //Load model for Apple.obj as mesh2


	object3.loadModel("..\\res\\Orange.obj"); //load model for Orange.obj as mesh3


	texture.init("..\\res\\BananaTexture.jpg"); //Initilise texture BananaTexture.jpg for mesh1
	texture2.init("..\\res\\AppleTexture.jpg"); //Initilise texture AppleTexture.jpg for mesh2
	texture3.init("..\\res\\OrangeTexture.jpg"); //Initilise texture OrangeTexture.jpg for mesh3

	shader.init("..\res\\shader"); //Initilise the shader

	myCamera.initCamera(glm::vec3(0, -5, -45), 70.35f, (float)gameDisplay.getWidth()/gameDisplay.getHeight(), 0.1f, 100.0f); //Initilise the camera and its location
	move = 0.0f; //set the counter for movement to 0.0f

	fruit1 = false; //set fruit1 object to false
	fruit2 = false; //set fruit2 object to false
	fruit3 = false; //set fruit3 object to false
	fruit4 = false; //set fruit4 object to false
	fruit5 = false; //set fruit5 object to false

	start = false; //set start to false


	BackgroundMusic = audioDevice.loadSound("..\\res\\BackgroundMusic.wav"); //load background music
	SplashSound = audioDevice.loadSound("..\\res\\SplashSound.wav"); //load the splash sound

	audioDevice.playSound(BackgroundMusic); //play the background music 

	collision = false;

}

void Game::drawText(const char *text, int length, int x, int y)
{

	glMatrixMode(GL_PROJECTION); //set matrix mode to projection
	double *matrix = new double[16]; //set matrix
	glGetDoublev(GL_PROJECTION_MATRIX, matrix); //return value for projection matrix and set matrix
	glLoadIdentity(); //replace the matrix with identity matrix
	glOrtho(0, 800, 0, 600, -5, 5); //multiply the matrix with orthographic matrix
	glMatrixMode(GL_MODELVIEW); //set matrix mode to model view
	glLoadIdentity; //repleace the matrix with identity matrix
	glPushMatrix(); //push the matrix
	glLoadIdentity(); //replace the matrix with identity matrix
	glRasterPos2i(x, y); //set raster positions
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]); //set font for the text
	}
	glPopMatrix(); //pop the matrix in stack
	glMatrixMode(GL_PROJECTION); //set matrix mode to projection
	glMatrixMode(GL_MODELVIEW); //set matrix mode to model view

}

void Game::playAudio(unsigned int Source, glm::vec3 pos)
{
	
}

void Game::gameLoop()
{
	while (gameState != GameState::EXIT) //while gamestate is not set to exit
	{
		processInput(); //process the inputs
		drawGame(); //draw the game
	}
}

void Game::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and makes sure to proceess set events being used
	{
		switch (evnt.type) //set event type
		{
		case SDL_KEYDOWN:

			if (evnt.key.keysym.sym == SDLK_RETURN) { //when enter is pressed

				if (start == false) //and if start is false
				{
					fruit1 = true; //set fruit1 to true
					start = true; //set start to true
				}
			}

			else if (evnt.key.keysym.sym == SDLK_ESCAPE) { //if escape is pressed
				exit(0); //exit the game
			}

			break;

		case SDL_KEYUP:

			if (evnt.key.keysym.sym == SDLK_SPACE) { //if space is pressed

				if (fruit1 == true) //and if fruit1 is true
				{
					fruit1 = false; //set fruit1 to false
					fruit2 = true; //set fruit2 to true
					audioDevice.playSound(SplashSound); //play the splash sound
				}

				else if (fruit2 == true) //if fruit2 is true
				{
					fruit2 = false; //set fruit2 to false
					fruit3 = true; //set fruit3 to true
					audioDevice.playSound(SplashSound); //play the splash sound
				}

				else if (fruit3 == true) //if fruit3 is true
				{
					fruit3 = false; //set fruit3 is false
					fruit4 = true; //set fruit4 is true
					audioDevice.playSound(SplashSound); //play the splash sound
				}

				else if (fruit4 == true) //if fruit 4 is true
				{
					fruit4 = false; //set fruit4 to false
					fruit5 = true; //set fruit5 to ture
					audioDevice.playSound(SplashSound); //play the splash sound
				}

				else if (fruit5 == true) //of fruit5 is true
				{
					fruit5 = false; //set fruit5 to false
					win = true; //set win bool to true
					audioDevice.playSound(SplashSound); //play the splash sound
				}
			}

			break;

			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
		}
	}
	
}

void Game::Collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{

	d = sqrtf((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.y) * (m2Pos.z - m1Pos.z));

	if (d <= radius)
	{
		collision = true;
	}

}

void Game::transformObject()
{
	if (fruit1 == true) { //if fruit1 is set to true

		transform.SetPos(glm::vec3(50.0, 20.0 * cosf(move) * 0.5, 20.0)); //transform the position of the object by gradually changing y coordinates
		transform.SetRot(glm::vec3(0.0, 0.5, move * 1.0)); //transform the rotation of the object by gradually chaning z roatation
		transform.SetScale(glm::vec3(0.5, 0.5, 0.5)); //set the scale of the object

	}

	if (fruit2 == true) { //if fruit2 is set to true

		transform.SetPos(glm::vec3(-50.0, 20.0 * cosf(move), 20.0)); //transform the position of the object by gradually changing y coordinates
		transform.SetRot(glm::vec3(0.0, 0.5, move * 1.0)); //transform the rotation of the object by gradually chaning z roatation
		transform.SetScale(glm::vec3(0.5, 0.5, 0.5)); //set the scale of the object

	}

	if (fruit3 == true) { //if fruit3 is set to true

		transform.SetPos(glm::vec3(0.0, 20.0 * sinl(move), 20.0)); //transform the position of the object by gradually changing y coordinates
		transform.SetRot(glm::vec3(0.0, 0.5, move * 1.0)); //transform the rotation of the object by gradually chaning z roatation
		transform.SetScale(glm::vec3(10.0, 10.0, 10.0)); //set the scale of the object

	}

	if (fruit4 == true) { //if fruit4 is set to true

		transform.SetPos(glm::vec3(25.0, 20.0 * cosf(move), 20.0)); //transform the position of the object by gradually changing y coordinates
		transform.SetRot(glm::vec3(0.0, 0.5, move * 1.0)); //transform the rotation of the object by gradually chaning z roatation
		transform.SetScale(glm::vec3(0.5, 0.5, 0.5)); //set the scale of the object

	}

	if (fruit5 == true) { //if fruit5 is set to true

		transform.SetPos(glm::vec3(-30.0, 20.0 * sinf(move), 20.0)); //transform the position of the object by gradually changing y coordinates
		transform.SetRot(glm::vec3(0.0, 0.5, move * 1.0)); //transform the rotation of the object by gradually chaning z roatation
		transform.SetScale(glm::vec3(0.5, 0.5, 0.5)); //set the scale of the object

	}


}


void Game::drawGame()
{

	radius = 0.6f; //set the radius to 0.6 for bounding sphere

	gameDisplay.clearDisplay(0.0f, 0.1f, 0.0f, 0.0f); //set the background colour


	if (start == false) {

		transform.SetPos(glm::vec3(15.0, 20.0, 20.0)); //set position for the text

		shader.Update(transform, myCamera); //update the position of mesh1 and current camera position

		std::string text; //set string for text
		text = "Fruit Splash! - The Game"; //type the text
		drawText(text.data(), text.size(), 0, 0); //draw the text


		transform.SetPos(glm::vec3(50.0, -5.0, 20.0)); //set position for the text

		shader.Update(transform, myCamera); //update the position of mesh1 and current camera position

		std::string text2; //set string for text2
		text2 = "Controls: Press SPACE to Destory The Fruit"; //type the text
		drawText(text2.data(), text2.size(), 0, 0); //draw the text


		transform.SetPos(glm::vec3(15.0, -35.0, 20.0)); //set position for the text

		shader.Update(transform, myCamera); //update the position of mesh1 and current camera position

		std::string text3; //set string for text3
		text3 = "Press ENTER to Start!"; //type the text
		drawText(text3.data(), text3.size(), 0, 0); //draw the text

	}

	if (fruit1 == true) {

		transformObject(); //transform the object

		texture.Bind(0); //bind the texture for mesh1

		shader.Update(transform, myCamera); //update the position of mesh1 and current camera position

		object1.draw(); //draw mesh1

		object1.meshSphere; //sphere data is not used at the moment

		transform.GetPos(); //get positions
	}


	if (fruit2 == true) {

		transformObject(); //transform the object

		texture3.Bind(0); //bind the texture3 for mesh3

		shader.Update(transform, myCamera); //update the position of mesh3 and current camera position

		object3.draw(); //draw mesh3

		object3.meshSphere; //sphere data is not used at the moment

		transform.GetPos(); //get positions

	}

	if (fruit3 == true) {

		transformObject(); //transform the object

		texture2.Bind(0); //bind the texture2 for mesh2 

		shader.Update(transform, myCamera); //update the position of mesh2 and current camera position

		object2.draw(); //draw mesh2

		object2.meshSphere; //sphere data is not used at the moment

		transform.GetPos(); //get positions

	}

	if (fruit4 == true) {

		transformObject(); //transform the object

		texture3.Bind(0); //bind texture3 for mesh3

		shader.Update(transform, myCamera); //update the position of mesh3 and current camera position

		object3.draw(); //draw mesh3

		object3.meshSphere; //sphere data is not used at the moment

		transform.GetPos(); //get positions

	}

	if (fruit5 == true) {

		transformObject(); //transform the object

		texture.Bind(0); //bind the texture for mesh1

		shader.Update(transform, myCamera); //update the position of mesh1 and current camera position

		object1.draw(); //draw mesh1

		object1.meshSphere; //sphere data is not used at the moment

		transform.GetPos(); //get positions

	}

	if (win == true) {

		transform.SetPos(glm::vec3(18.0, -5.0, 20.0)); //set position for the text

		shader.Update(transform, myCamera); //update the position of mesh1 and current camera position

		std::string text4; //set string for text4
		text4 = "You Win! : Press ESCAPE to Exit"; //type the text
		drawText(text4.data(), text4.size(), 0, 0); //draw the text

	}

	shader.Bind(); //bind the shader

	move = move + 0.03f; //set the movement counter to add 0.01 every frame

	gameDisplay.swapBuffer(); //swap the buffer
}
