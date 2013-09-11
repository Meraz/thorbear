#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H
#include "Fmod/inc/fmod.hpp"
#include "Fmod/inc/fmod_errors.h"
#include "windows.h"
#include "stdio.h"
#include <string>
#define NUMBER_OF_GAMESOUNDS 3
enum SOUNDTYPE
{
	ballBounce,
	enemyFire,
	enemyDeath
};
class SoundHandler
{
private:
	//fmod stuff
	FMOD::System*		m_system;
	FMOD_RESULT			m_result;
	FMOD_SPEAKERMODE	m_speakerMode;
	FMOD_CAPS			m_caps;
	FMOD::Sound*		m_backGroundStream;
	FMOD::Sound*		m_gameSound[NUMBER_OF_GAMESOUNDS];
	FMOD::Channel*		m_BackGroundChannel;
	FMOD::Channel*		m_gameSoundChannel[NUMBER_OF_GAMESOUNDS];
	unsigned int		m_version;
	int					m_numDrivers;
	char				m_name[256];

private:
	void ErrorCheck(FMOD_RESULT p_result);
	void AudioLoader(std::string p_name, SOUNDTYPE p_soundType);

public:
	SoundHandler();
	~SoundHandler();
	void Initialize();
	void PlayBackGroundSound(std::string p_name);
	void Update();
	void PlaySound(SOUNDTYPE p_soundType);
};
#endif