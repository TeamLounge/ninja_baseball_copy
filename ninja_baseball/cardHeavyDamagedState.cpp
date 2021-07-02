#include "stdafx.h"
#include "cardHeavyDamagedState.h"
#include "cardDeathState.h"
#include "cardSmallDamagedState.h"
#include "card.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardPunchAttackState.h"
#include "cardDeathState.h"
#include "cardLandState.h"

cardState * cardHeavyDamagedState::inputHandle(card * card)
{
	if (card->_currentFrameX == card->_card.img->getMaxFrameX() + 1 &&
		card->_deathCount < 4)
	{
		card->_isCardHeavyDamaged = false;
		card->_isCardHeavyDamagedState = false;
		card->_isCardSmallDamagedState = false;
		card->_isGreenCatchFrontCombo = false;
		card->_isGreenCatchBackAttack = false;
		card->_isGreenAttack1 = false;
		card->_isGreenAttack2 = false;
		card->_isGreenAttack3 = false;
		return new cardIdleState();
	}

	if (card->_currentFrameX == card->_card.img->getMaxFrameX() + 1 &&
		card->_deathCount >= 4)
	{
		card->_isGreenCatchFrontCombo = false;
		card->_isGreenCatchBackAttack = false;
		card->_isCardHeavyDamagedState = false;
		card->_isCardHeavyDamaged = false;
		return new cardDeathState();
	}

	return nullptr;
}

void cardHeavyDamagedState::update(card * card)
{
	frameCount++;
	if (frameCount >= 15)
	{
		frameCount = 0;
		if (card->_currentFrameX == 0 && card->_isJump)
		{
			card->_currentFrameX = 0;
		}

		//else card->_currentFrameX++;

		if (card->_currentFrameX == card->_card.img->getMaxFrameX() && !card->_isJump)
		{
			readyCount++;
			if (readyCount >= 2)
			{
				card->_currentFrameX = card->_card.img->getMaxFrameX() + 1;
			}

		}

		if (!card->_isJump && card->_currentFrameX < card->_card.img->getMaxFrameX())
		{
			card->_currentFrameX++;
		}
	}


	jump(card);
}

void cardHeavyDamagedState::enter(card * card)
{
	card->_card.img = IMAGEMANAGER->findImage("card_stun");
	card->_imageName = "card_stun";

	if (!card->_isGreenCatchFrontCombo &&
		!card->_isGreenCatchBackAttack)
	{
		card->_deathCount += 2;
	}

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

	card->_isCardHeavyDamagedState = true;
	card->_isCardMoveState = false;

	if (card->_isCardSmallDamaged)
	{
		card->_isCardSmallDamaged = false;
	}

	if (card->_isGreenCatchBackAttack || card->_isGreenCatchFrontCombo)
	{
		jumpPower = 15.5f;
		gravity = 0.55f;
	}

	else
	{
		jumpPower = 12.5f;
		gravity = 0.55f;
	}

	readyCount = 0;
	deathCount = 0;
	catchCount = 0;

	_isRightWall = false;
	_isLeftWall = false;
}

void cardHeavyDamagedState::exit(card * card)
{
}

void cardHeavyDamagedState::jump(card * card)
{
	if (card->_isJump && card->_isGreenCatchBackAttack && !card->_isGreenCatchFrontCombo)
	{
		card->_card.y -= jumpPower;
		jumpPower -= gravity;
		if (card->_currentFrameY == 1) card->_card.x -= 13.7f;
		if (card->_currentFrameY == 0) card->_card.x += 13.7f;
	}

	if (card->_isJump && !card->_isGreenCatchBackAttack && !card->_isGreenCatchFrontCombo)
	{
		card->_card.y -= jumpPower;
		jumpPower -= gravity;
		if (card->_currentFrameY == 1) card->_card.x -= 1.5f;
		if (card->_currentFrameY == 0) card->_card.x += 1.5f;
	}

	if (card->_isJump && !card->_isGreenCatchBackAttack && card->_isGreenCatchFrontCombo)
	{
		card->_card.y -= jumpPower;
		jumpPower -= gravity;
		if (card->_currentFrameY == 1) card->_card.x -= 13.7f;
		if (card->_currentFrameY == 0) card->_card.x += 13.7f;
	}

	if (card->_isJump)
	{
		card->_card.y -= jumpPower;
		jumpPower -= gravity;

		if (card->_card.rc.right > BACKGROUNDX)
		{
			_isRightWall = true;
			_isLeftWall = false;
		}

		if (card->_card.rc.left < BACKGROUNDX - CAMERAX)
		{
			_isRightWall = false;
			_isLeftWall = true;
		}

		if (card->_currentFrameY == 0)
		{
			if (_isRightWall)
			{
				if (card->_isGreenCatchBackAttack ||
					card->_isGreenCatchFrontCombo) card->_card.x -= 13.7f;
				
				else card->_card.x -= 1.5f;
			}
			
			if (_isLeftWall)
			{
				if (card->_isGreenCatchBackAttack ||
					card->_isGreenCatchFrontCombo) card->_card.x += 13.7f;

				else card->_card.x += 1.5f;
			}
			if (!_isRightWall && !_isLeftWall)
			{
				if (card->_isGreenCatchBackAttack ||
					card->_isGreenCatchFrontCombo) card->_card.x += 13.7f;

				else card->_card.x += 1.5f;
			}
		}
		
		if (card->_currentFrameY == 1)
		{
			if (_isRightWall)
			{
				if (card->_isGreenCatchBackAttack ||
					card->_isGreenCatchFrontCombo) card->_card.x -= 13.7f;

				else card->_card.x -= 1.5f;
			}
			if (_isLeftWall)
			{
				if (card->_isGreenCatchBackAttack ||
					card->_isGreenCatchFrontCombo) card->_card.x += 13.7f;

				else card->_card.x += 1.5f;
			}
			if (!_isRightWall && !_isLeftWall)
			{
				if (card->_isGreenCatchBackAttack ||
					card->_isGreenCatchFrontCombo) card->_card.x -= 13.7f;

				else card->_card.x -= 1.5f;
			}
		}

	}

	if ((card->_cardShadow.rc.bottom + card->_cardShadow.rc.top) / 2 < card->_card.rc.bottom)
	{
		card->_card.rc.bottom = card->_jumpShadowY;
		jumpPower = 0;
		gravity = 0;
		card->_isJump = false;
	}
}
