#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbLandState::inputHandle(greenBaseball * greenBaseball)
{
	return nullptr;
}

void gbLandState::update(greenBaseball * greenBaseball)
{
}

void gbLandState::enter(greenBaseball * greenBaseball)
{
}

void gbLandState::exit(greenBaseball * greenBaseball)
{
}
