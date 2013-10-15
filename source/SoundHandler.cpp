#include "SoundHandler.h"

#include <cstring>

SoundHandler::SoundHandler()
{
	//empty 'cause initialize functions is the way to go
}
SoundHandler::~SoundHandler()
{
	for(int i = 0; i < NUMBER_OF_GAMESOUNDS; i++)
	{
		if(m_gameSound[i] != NULL)
			m_gameSound[i]->release();
	}
	m_backGroundStream->release();
	m_system->release();
	
}
/*Starts the fmod systems and loads the gamesounds*/
void SoundHandler::Initialize()
{
	m_result = FMOD::System_Create(&m_system);
	ErrorCheck(m_result);

	m_result = m_system->getVersion(&m_version);
	ErrorCheck(m_result);

	if(m_version < FMOD_VERSION)
		printf("Error you are using a old version of FMOD %08x. This program requires %08x\n", m_version, FMOD_VERSION);
	m_result = m_system->getNumDrivers(&m_numDrivers);
	ErrorCheck(m_result);

	if( m_numDrivers == 0)
	{
		m_result = m_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ErrorCheck(m_result);
	}
	else
	{
		m_result = m_system->getDriverCaps(0,&m_caps,0,&m_speakerMode);
		ErrorCheck(m_result);
	}

	m_result =  m_system->setSpeakerMode(m_speakerMode);
	ErrorCheck(m_result);

	if(m_caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		/*
		The user has the 'Acceleration' slider set to off! This is really bad
		for latency! You might want to warn the user about this.
		*/
		m_result = m_system->setDSPBufferSize(1024,10);
		ErrorCheck(m_result);
	}
	m_result = m_system->getDriverInfo(0, m_name, 256, 0);
	ErrorCheck(m_result);

	if( strstr(m_name, "SigmaTel"))
	{
		/*
		"Sigmatel" sound devices crackle for some reason if the format is PCM 16bit.
		PCM floating point output seems to solve it.
		*/
		m_result = m_system->setSoftwareFormat(4800, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
		ErrorCheck(m_result);
	}
	m_result = m_system->init(1024, FMOD_INIT_NORMAL, 0);
	if(m_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		/*
		Ok, the speaker mode selected isn't supported by this soundcard. Switch it
		back to stereo...
		*/
		m_result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		ErrorCheck(m_result);

		/*
		... and re-init.
		*/
		m_result = m_system->init(1024, FMOD_INIT_NORMAL, 0);
	}
	ErrorCheck(m_result);

	//Load all audio ADD AUDIO HERE
	AudioLoader("Audio/bounce.wav", BALLBOUNCE);
	AudioLoader("Audio/Enemyfire.mp3", ENEMYFIRE);
	AudioLoader("Audio/Enemydeath.wav", ENEMYDEATH);
	AudioLoader("Audio/PowerupPickup.wav", POWERUPPICKUP);
	
}

void SoundHandler::AudioLoader(std::string p_name, SOUNDTYPE p_soundType)
{
	//remember to increase the NUMBER_OF_GAMESOUNDS define in SoundHandler.h if you add new sounds
	const char* l_temp = p_name.c_str();
	m_system->createSound(l_temp, FMOD_LOOP_OFF, 0, &m_gameSound[p_soundType]);

}
/*Call this each time a sound should be played*/
void SoundHandler::PlayGameSound(SOUNDTYPE p_soundType) 
{
	FMOD::Channel* l_channel;
	m_system->playSound(FMOD_CHANNEL_FREE, m_gameSound[p_soundType], true, &l_channel);
	
	if(p_soundType == ENEMYFIRE)
	{
		l_channel->setVolume(0.1f);
		FMOD::DSP* l_pitch;
		m_system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &l_pitch);
		int temp = rand();
		l_pitch->setParameter(FMOD_DSP_PITCHSHIFT_PITCH, float(temp)/RAND_MAX*1.5f+0.5f);
		l_channel->addDSP(l_pitch,0);
	}
	else if( p_soundType == POWERUPPICKUP)
		l_channel->setVolume(0.2f);

	l_channel->setPaused(false);
}
//Call this once to start the background sound
void SoundHandler::PlayBackGroundSound(std::string p_name) //Play background sound
{
	m_BackGroundChannel->stop();
	const char* l_temp = p_name.c_str();
	m_system->createStream(l_temp,FMOD_DEFAULT, 0, &m_backGroundStream);
	m_system->playSound(FMOD_CHANNEL_FREE, m_backGroundStream, false, &m_BackGroundChannel);
	m_BackGroundChannel->setMode(FMOD_LOOP_NORMAL);
	m_BackGroundChannel->setLoopCount(-1);
	m_BackGroundChannel->setVolume(0.1f);
}
//Updates the FMODSystem
void SoundHandler::Update()
{
	m_system->update();

}
//the worlds best errorchecker
void SoundHandler::ErrorCheck(FMOD_RESULT p_result)
{
	if(p_result !=  FMOD_OK)
		perror("Error initializing SoundHandler" + p_result);
	//add check here later
}
