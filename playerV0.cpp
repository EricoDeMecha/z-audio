#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h"

#include <thread>
#include <chrono>

bool succeedWarn(const std::string &message , FMOD_RESULT result)
{
	if(result != FMOD_OK)
	{
		std::cerr << message << " : "<< result<< " "<< FMOD_ErrorString(result) << std::endl;
		return false;
	}
	return true;
}

FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL *channelControl, FMOD_CHANNELCONTROL_TYPE  controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void *commandData1, void *commandData2)
{
	std::cout << "Callback called for " << controlType << std::endl;
       return FMOD_OK;	
}
int main()
{
	FMOD_RESULT result;// status 
	// create the main system object
	FMOD::System *system = nullptr;
	result = FMOD::System_Create(&system);
	if(!succeedWarn("FMOD:: Failed to create the system object", result))
		//quit
		return -1;
	// initialize FMOD
	result = system->init(512, FMOD_INIT_NORMAL, nullptr);
	if(!succeedWarn("FMOD:: Failed to initialize FMOD", result))
		return -1;
	//create the channel group
	FMOD::ChannelGroup *channelGroup = nullptr;
	result = system->createChannelGroup("Mp3 player", &channelGroup);
	if(!succeedWarn("FMOD:: Failed to create the channel group", result))
		return -1;
	// create the sound
	FMOD::Sound *sound = nullptr;
	system->createSound("coming.mp3", FMOD_DEFAULT, nullptr, &sound);

	// play the sound
	FMOD::Channel *channel = nullptr;
	result = system->playSound(sound, nullptr, false, &channel);
	if(!succeedWarn("FMOD: Failed to play the sound", result))
		return -1;
	// assign the channel to the group
	result = channel->setChannelGroup(channelGroup);
	if(!succeedWarn("FMOD: Failed to assign the channel to the group", result))
		return -1;

	// set a callback on the channel
	channel->setCallback(&channelGroupCallback);
	if(!succeedWarn("FMOD: Failed to set the callback for sound", result))
		return -1;

	bool isPlaying = false;
	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		channel->isPlaying(&isPlaying);
		system->update();
	}while(isPlaying);

	//clean up
	sound->release();
	channelGroup->release();
	system->release();
	

	return 0;
}
