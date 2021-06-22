#include "Sound.h"

#include <iostream>

//FOMD ����
System* pSystem;
Sound* pSound[2];
Channel* pChannel[2];

//���� �ý���
void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(2, FMOD_INIT_NORMAL, NULL);

	pSystem->createSound("sound1.wav", FMOD_DEFAULT, NULL, &pSound[0]);
	pSystem->createSound("sound2.wav", FMOD_DEFAULT, NULL, &pSound[1]);
}

//�Ҹ� ���
void Play(int Sound_num, int channelNumber)
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel[channelNumber]);
}