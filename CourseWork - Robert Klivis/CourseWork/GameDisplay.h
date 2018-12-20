#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class GameDisplay
{
public:
	GameDisplay(); //constructor for GameDispaly
	~GameDisplay(); //deconstructor for GameDispaly
	void initDisplay(); //initilise display
	void swapBuffer(); //swap buffers
	void clearDisplay(float r, float g, float b, float a);

	float getWidth(); //float for screen width getter
	float getHeight(); //float for screen height getter

private:

	void returnError(std::string errorString);
	
	SDL_GLContext glContext; //set variables that hold context
	SDL_Window* sdlWindow; //pointer for window
	float screenWidth; //float for screen width
	float screenHeight; //float for screen height
};

