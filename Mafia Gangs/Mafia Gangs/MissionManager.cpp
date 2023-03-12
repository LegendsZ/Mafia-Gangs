#include "MissionManager.h"

bool MissionManager::loaded = false;
std::string MissionManager::saveFilePath = "data.txt";
int MissionManager::currentMissionIndex = 0;
std::vector<MissionBase*> MissionManager::missions;

bool MissionManager::loadMissionData()
{
	std::ifstream fileInput;
	fileInput.open(saveFilePath);
	if (!fileInput.is_open()) {
		std::cout << "Error reading file!\nCreating a new file!\n";
		std::ofstream fileOutput(saveFilePath);
		fileOutput.close();
	}
	else {
		//reading goes here
		fileInput.close();
	}

	return true;
}

void MissionManager::startOrContinue()
{
	missions[currentMissionIndex]->startOrContinue();
}

bool MissionManager::save()
{
	std::ofstream fileOutput(saveFilePath);
	if (fileOutput.is_open()) {
		//write
	}
	else { 
		return false;
	}
	fileOutput.close();
	return true;
}

void MissionManager::close()
{
}

void MissionManager::pickMissionByIndex(int index)
{
	missions[index]->reset();
	missions[index]->startOrContinue();
}

void MissionManager::resetByIndex(int index)
{
	missions[index]->reset();
}

void MissionManager::reset()
{
	for (MissionBase* mission : missions) {
		mission->reset();
	}
}
