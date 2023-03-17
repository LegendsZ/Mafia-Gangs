#pragma once
#include "Dialog.h"

class MissionBase {
public:
	virtual bool startOrContinue()=0;
	virtual bool reset()=0;
	float completion;
private:
};