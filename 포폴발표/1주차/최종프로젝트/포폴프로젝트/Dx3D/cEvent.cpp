#include "stdafx.h"
#include "cEvent.h"


cEvent::cEvent()
{
}


cEvent::~cEvent()
{
}

void cEvent::update()
{
	if (_switch){ EVENT(); }
}
