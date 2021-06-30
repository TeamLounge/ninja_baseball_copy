#include "stdafx.h"
#include "blueBaseball.h"
#include "bbDamagedState.h"

bbState * bbDamagedState::inputHandle(blueBaseball * blueBaseball)
{
	return nullptr;
}

void bbDamagedState::update(blueBaseball * blueBaseball)
{
	/*frameCount++;

	if (frameCount)
	{
		
	}*/
}

void bbDamagedState::enter(blueBaseball * blueBaseball)
{
	blueBaseball->_blueBaseball.img = IMAGEMANAGER->findImage("bBaseball_damaged");
	
	frameCount = 0;
	
	if (!blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(1);
	}
	if (blueBaseball->isRight)
	{
		blueBaseball->setCurrentFrameY(0);
	}
	blueBaseball->setCurrentFrameX(0);
}

void bbDamagedState::exit(blueBaseball * blueBaseball)
{
}
