#pragma once

#include "list.h"

typedef struct LeaderboardEntry {
    char name[50];
    int score;
} LeaderboardEntry;

DEFINE_LIST(LeaderboardEntries, LeaderboardEntry);