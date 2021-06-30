#include "stdafx.h"
#include "greenBaseball.h"
#include "gbIdleState.h"
#include "gbHangState.h"
#include "gbLandState.h"
#include "gbAttackPunchState.h"
#include "gbDamagedState.h"
#include "gbDeathState.h"

gbState * gbHangState::inputHandle(greenBaseball * greenBaseball)
{
	return nullptr;
}

void gbHangState::update(greenBaseball * greenBaseball)
{
}

void gbHangState::enter(greenBaseball * greenBaseball)
{
}

void gbHangState::exit(greenBaseball * greenBaseball)
{
}
