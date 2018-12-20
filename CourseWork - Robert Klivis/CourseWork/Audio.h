#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Audio
{
	struct data {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	struct Vector3
	{
		float x, y, z;
	};
	std::vector<data> datas;
	ALCcontext* context;
	ALCdevice *device;
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	Audio(); //constructor for audio
	~Audio(); //deconstructor for audio
	unsigned int loadSound(const char* filename); //unsigned integer for loadSound
	void deleteSound(unsigned int id); //delete sound
	void playSound(unsigned int id); //play the sound
	void playSound(unsigned int id, glm::vec3& pos); //play the sound with set position
	void stopSound(unsigned int id); //stop playing the sound
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt); //set the listeners position and direction that camera is looking

private:
	
};
