#include "stdafx.h"
#include "cardSmallDamagedState.h"
#include "card.h"
#include "cardPunchAttackState.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardDeathState.h"
#include "cardHeavyDamagedState.h"
#include "cardLandState.h"

cardState * cardSmallDamagedState::inputHandle(card * card)
{
	frameCount++;
	if (frameCount >= 35 && card->_deathCount < 4)
	{
		card->_isGreenAttack1 = false;
		card->_isGreenAttack2 = false;
		card->_isGreenAttack3 = false;
		card->_isCardSmallDamagedState = false;
		card->_isCardSmallDamaged = false;
		card->_isGreenCatch = false;
		return new cardIdleState();
	}

	if (frameCount >= 35 && card->_deathCount >= 4)
	{ 
		card->_isGreenAttack1 = false;
		card->_isGreenAttack2 = false;
		card->_isGreenAttack3 = false;
		card->_isCardSmallDamagedState = false;
		card->_isCardSmallDamaged = false;
		card->_isGreenCatch = false;
		return new cardDeathState();
	}

	if (card->_isGreenAttack1)
	{
		card->_isGreenAttack1 = false;
		card->_deathCount++;
		card->_currentFrameX = 0;
	}

	if (card->_isGreenAttack2)
	{
		card->_isGreenAttack2 = false;
		card->_deathCount++;
		card->_currentFrameX = 1;
	}

	if (card->_isGreenAttack3)
	{
		card->_isJump = true;
		card->_isGreenAttack3 = false;
		card->_isCardSmallDamagedState = false;
		card->_deathCount++;
		card->_currentFrameX = 2;
		return new cardHeavyDamagedState();
	}

	if (card->_isGreenCatch)
	{
		frameCount = 0;

		if (card->_isGreenCatchAttack && card->_currentFrameX == 0)
		{
			card->_currentFrameX = 1;
			card->_deathCount++;
			card->_isGreenCatchAttack = false;
		}
		if (card->_isGreenCatchAttack && card->_currentFrameX == 1)
		{
			card->_currentFrameX = 2;
			card->_deathCount++;
			card->_isGreenCatchAttack = false;
		}
		if (card->_isGreenCatchAttack && card->_currentFrameX == 2)
		{
			card->_currentFrameX = 3;
			card->_deathCount++;
			card->_isGreenCatchAttack = false;
		}

		if (card->_isGreenCatchAttack && card->_currentFrameX == 3)
		{
			card->_isCardSmallDamagedState = false;
			card->_isCardSmallDamaged = false;
			card->_isGreenCatch = false;
			card->_isGreenCatchAttack = false;
			return new cardLandState();
		}

		if (card->_isGreenCatchBackAttack)
		{
			card->_isJump = true;
			card->_isGreenCatch = false;
			card->_isCardSmallDamagedState = false;
			card->_deathCount += 2;
			return new cardHeavyDamagedState();
		}

		if (card->_isGreenCatchFrontCombo)
		{
			card->_isJump = true;
			card->_isGreenCatch = false;
			card->_isCardSmallDamagedState = false;
			card->_deathCount += 2;
			return new cardHeavyDamagedState();
		}
	}

	return nullptr;
}

void cardSmallDamagedState::update(card * card)
{
}

void cardSmallDamagedState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_damaged");
	card->_imageName = "card_damaged";

	if (!card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 0;
	}

	if (card->_isLeft)
	{
		card->_currentFrameX = 0;
		card->_currentFrameY = 1;
	}

	card->_isCardMoveState = false;
	card->_isCardSmallDamagedState = true;
	card->_isGreenCatchAttackPre = false;

	frameCount = 0;
	readyCount = 0;
	count = 0;
	frameCatchCount = 0;
}

void cardSmallDamagedState::exit(card * card)
{

}
