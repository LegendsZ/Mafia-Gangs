#pragma once
#include "MissionBase.h"

class MissionOne : MissionBase {
public:
	static MissionOne* self;
	bool startOrContinue();
	static int mainLogic(void* nullData);
	bool reset();
	bool draw();

	//game vars below
	Dialog* dialog;
private:
};