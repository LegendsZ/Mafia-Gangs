#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "MissionBase.h"

class MissionManager {
public:
	static std::vector<MissionBase*> missions;

	static bool loadMissionData();
	static bool save();
	static void startOrContinue();
	static void close();
	static void pickMissionByIndex(int index);
	static void resetByIndex(int index);
	static void reset();
	static int currentMissionIndex;
	static std::string saveFilePath;
	static bool loaded;
private:
};