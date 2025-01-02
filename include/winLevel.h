#pragma once

#include "BeEngineUI.h"
#include "level.h"

DEFINE_LEVEL(WinLevel);

void initializeWinLevelUI();
void submitButtonClicked(ButtonUIComponent* button, UICanvas* canvas);