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

cardState * cardHeavyDamagedState::inputHandle(card * card)
{
	return nullptr;
}

void cardHeavyDamagedState::update(card * card)
{
}

void cardHeavyDamagedState::enter(card * card)
{
}

void cardHeavyDamagedState::exit(card * card)
{
}
