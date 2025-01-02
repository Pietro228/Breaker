#pragma once

int sound_init();
void sound_play2D(const char* path, int loops);
void _sound_channelFinished(int channel);