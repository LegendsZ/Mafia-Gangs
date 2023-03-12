#pragma once
#include "Dialog.h"

class MissionBase {
public:
	virtual bool startOrContinue();
	virtual bool reset();
	float completion;
private:
};