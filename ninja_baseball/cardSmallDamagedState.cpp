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
		card->_isRedAttack1 = false;
		card->_isGreenAttack2 = false;
		card->_isRedAttack2 = false;
		card->_isGreenAttack3 = false;
		card->_isRedAttack3 = false;
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

	if (card->_isRedHomeRunAttack)
	{
		card->_isJump = true;
		card->_isRedAttack1 = false;
		card->_isRedAttack2 = false;
		card->_isCardSmallDamagedState = false;
		return new cardHeavyDamagedState();
	}

	if ((card->_isGreenAttack1 && atkCnt == 0) ||
		(card->_isRedAttack1 && atkCnt == 0))
	{
		atkCnt++;
		card->_isGreenAttack1 = false;
		card->_isRedAttack1 = false;
		card->_deathCount++;
		card->_currentFrameX = 0;
	}

	if ((card->_isGreenAttack2 && atkCnt == 1) ||
		(card->_isRedAttack2 && atkCnt == 1))
	{
		atkCnt++;
		card->_isGreenAttack2 = false;
		card->_isRedAttack2 = false;
		card->_deathCount++;
		card->_currentFrameX = 1;
	}

	if ((card->_isGreenAttack3 && atkCnt == 2) ||
		(card->_isRedAttack3 && atkCnt == 2))
	{
		atkCnt++;
		card->_isJump = true;
		card->_isGreenAttack3 = false;
		card->_isRedAttack3 = false;
		card->_isCardSmallDamagedState = false;
		card->_currentFrameX = 2;
		return new cardHeavyDamagedState();
	}

	if (!card->_isGreenCatch && card->_isGreenCatchAttackPre)
	{
		card->_isCardSmallDamaged = false;
		card->_isCardSmallDamagedState = false;
		return new cardIdleState();
	}

	if (card->_isGreenCatch)
	{
		frameCount = 0;
		card->_isGreenCatchAttackPre = true;

		if (card->_isGreenCatchAttack && card->_currentFrameX == 0)
		{
			card->_currentFrameX = 1;
			card->_deathCount++;
			card->_isGreenCatchAttack = false;
			card->_isGreenCatchAttackPre = false;
		}

		if (card->_isGreenCatchAttack && card->_currentFrameX == 1)
		{
			card->_currentFrameX = 2;
			card->_deathCount++;
			card->_isGreenCatchAttack = false;
			card->_isGreenCatchAttackPre = false;
		}

		if (card->_isGreenCatchAttack && card->_currentFrameX == 2)
		{
			card->_currentFrameX = 3;
			card->_deathCount++;
			card->_isGreenCatchAttack = false;
			card->_isGreenCatchAttackPre = false;
		}

		if (card->_isGreenCatchAttack && card->_currentFrameX == 3)
		{
			card->_isCardSmallDamagedState = false;
			card->_isCardSmallDamaged = false;
			card->_isGreenCatch = false;
			card->_isGreenCatchAttack = false;
			card->_isGreenCatchAttackPre = false;
			return new cardLandState();
		}

		if (card->_isGreenCatchBackAttack)
		{
			card->_isJump = true;
			card->_isGreenCatch = false;
			card->_isCardSmallDamagedState = false;
			card->_isGreenCatchAttackPre = false;
			card->_deathCount += 2;
			return new cardHeavyDamagedState();
		}

		if (card->_isGreenCatchFrontCombo)
		{
			card->_isJump = true;
			card->_isGreenCatch = false;
			card->_isCardSmallDamagedState = false;
			card->_isGreenCatchAttackPre = false;
			card->_deathCount += 2;
			return new cardHeavyDamagedState();
		}
	}

	if (card->_isRedDynamiteDance)
	{
		card->_isRedDynamiteOn = true;
		frameCount = 0;
		count++;
		if (count >= 10)
		{
			count = 0;
			card->_currentFrameX++;
			if (card->_currentFrameX == card->_card.img->getMaxFrameX())
			{
				card->_currentFrameX = 0;
			}
			card->_deathCount++;
		}
	}

	if (!card->_isRedDynamiteDance && card->_isRedDynamiteOn)
	{
		card->_isJump = true;
		card->_isCardSmallDamagedState = false;
		return new cardHeavyDamagedState();
	}

	if (!card->_isRedCatch && card->_isRedCatchAttackPre)
	{
		card->_isCardSmallDamaged = false;
		card->_isCardSmallDamagedState = false;
		return new cardIdleState();
	}

	if (card->_isRedCatch)
	{
		frameCount = 0;
		card->_isRedCatchAttackPre = true;

		if (card->_isRedCatchAttack && card->_currentFrameX == 0)
		{
			card->_currentFrameX = 1;
			card->_deathCount++;
			card->_isRedCatchAttack = false;
			card->_isRedCatchAttackPre = false;
		}

		if (card->_isRedCatchAttack && card->_currentFrameX == 1)
		{
			card->_currentFrameX = 2;
			card->_deathCount++;
			card->_isRedCatchAttack = false;
			card->_isRedCatchAttackPre = false;
		}

		if (card->_isRedCatchAttack && card->_currentFrameX == 2)
		{
			card->_isCardSmallDamagedState = false;
			card->_isCardSmallDamaged = false;
			card->_isRedCatch = false;
			card->_isRedCatchAttack = false;
			card->_isRedCatchAttackPre = false;
			return new cardLandState();
		}

		if (card->_isRedHomeRunAttack)
		{
			card->_isJump = true;
			card->_isRedCatch = false;
			card->_isCardSmallDamagedState = false;
			card->_isRedCatchAttackPre = false;
			card->_deathCount += 2;
			return new cardHeavyDamagedState();
		}

		if (card->_isRedThrow)
		{
			card->_isJump = true;
			card->_isRedCatch = false;
			card->_isCardSmallDamagedState = false;
			card->_isRedCatchAttackPre = false;
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
	card->_isRedCatchAttackPre = false;
	card->_isRedDynamiteOn = false;

	frameCount = 0;
	readyCount = 0;
	count = 0;
	frameCatchCount = 0;
	atkCnt = 0;
}

void cardSmallDamagedState::exit(card * card)
{

}
