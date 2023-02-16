#pragma once

class MissionBase {
public:
	virtual bool startOrContinue();
	virtual bool reset();
	float completion;
private:
};