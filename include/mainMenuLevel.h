#pragma once

#include "buttonUIComponent.h"
#include "level.h"
#include "uiCanvas.h"

DEFINE_LEVEL(MainMenuLevel);
void event_playButton_clicked(ButtonUIComponent *comp, UICanvas *canvas);
void event_quitButton_clicked(ButtonUIComponent *comp, UICanvas *canvas);
void showLeaderboard();