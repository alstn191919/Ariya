#pragma once
class cEvent
{
public:
	bool _switch;
	cOBB * obb;

public:
	virtual void EVENT(){};
	virtual void update();

	cEvent();
	virtual ~cEvent();
};

