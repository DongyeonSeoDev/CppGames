#pragma once

#include <fmod.hpp>
using namespace FMOD;

//FOMD ����
extern System* pSystem;
extern Sound* pSound[2];
extern Channel* pChannel[2];

//���� �ý���
void SoundSystem();
//�Ҹ� ���
void Play(int Sound_num, int channelNumber);