#include "stdafx.h"
#include "cardDeathState.h"
#include "card.h"
#include "cardDashAttackState.h"
#include "cardIdleState.h"
#include "cardMoveState.h"
#include "cardPunchAttackState.h"
#include "cardSmallDamagedState.h"
#include "cardHeavyDamagedState.h"

cardState * cardDeathState::inputHandle(card * card)
{
	return nullptr;
}

void cardDeathState::update(card * card)
{
}

void cardDeathState::enter(card * card)
{
}

void cardDeathState::exit(card * card)
{
}

void cardDeathState::jump(card * card)
{
}
