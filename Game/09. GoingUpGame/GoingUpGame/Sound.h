#pragma once

#include <fmod.hpp>
using namespace FMOD;

//FOMD 변수
extern System* pSystem;
extern Sound* pSound[2];
extern Channel* pChannel[2];

//사운드 시스템
void SoundSystem();
//소리 재생
void Play(int Sound_num, int channelNumber);