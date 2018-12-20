#include "GameDisplay.h"

GameDisplay::GameDisplay()
{
	sdlWindow = nullptr; // initilaise debugging
	screenWidth = 1024.0f; //set the screen width
	screenHeight = 768.0f; //set the screen height
}

GameDisplay::~GameDisplay()
{
	SDL_GL_DeleteContext(glContext); //set to delete context
	SDL_DestroyWindow(sdlWindow); //set to delete window
	SDL_Quit(); //quit SDL window
}

float GameDisplay::getWidth() { return screenWidth; } //getter for width of the screen
float GameDisplay::getHeight() { return screenHeight; } //getter for height of the screen

void GameDisplay::returnError(std::string errorString)
{
	std::cout << errorString << std::endl; 
	std::cout << "press any key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit(); //quit SDL window
}

void GameDisplay::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow); //swap the buffers
}

void GameDisplay::clearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //set clear colour and depth buffer
}

void GameDisplay::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initialise everything for SDL

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //set minimum number of bits being used to display colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //set the buffers for z
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //seet the double buffer

	sdlWindow = SDL_CreateWindow("Fruit Splash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); //creates the game window

	if (sdlWindow == nullptr) //if sdl window has not been created
	{
		returnError("Window has not been created!"); //dispaly the message
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr) //if glContext has not been created
	{
		returnError("SDL_GL context has not been created!"); //display the meessage
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) //if glew has not been initalised
	{
		returnError("GLEW failed has not been initialised!"); //display the message
	}

	glEnable(GL_DEPTH_TEST); //enables buffering for z
	glEnable(GL_CULL_FACE); //makes sure not to draw faces that are not facing the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}
