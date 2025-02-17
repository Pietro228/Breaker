#pragma once

#include "engineApi.h"

int sound_init();
BEENGINE_API void sound_play2D(const char* path, int loops);
void _sound_channelFinished(int channel);